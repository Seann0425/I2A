#include <bits/stdc++.h>
using namespace std;

// Segment Tree without lazy tag
template <typename T, typename S>
class SegmentTree {
public:
    size_t size;
    vector<T> tree;
    const T DEFAULT = T{};
    SegmentTree(size_t n) {
        size = 1;
        while (size < n) size *= 2; // perfect binary tree
        tree.resize(2 * size - 1, DEFAULT);
    }

    T merge(T a, T b) { return a + b; }

    T combine(T a, T b) { return T{a.length + b.length, 0, 0}; }

    // build segment tree from source array
    void build(vector<T> &src, size_t idx, size_t left_close, size_t right_open) {
        // top down
        if (right_open - left_close == 1) {
            if (left_close < src.size()) tree[idx] = src[left_close];
            return;
        }

        size_t mid = left_close + (right_open - left_close) / 2;
        build(src, 2 * idx + 1, left_close, mid);
        build(src, 2 * idx + 2, mid, right_open);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void build(vector<T> &src) { build(src, 0, 0, size); }

    // set value at index
    void set(size_t i_src, const T &val, size_t idx, size_t left_close, size_t right_open) {
        if (right_open - left_close == 1) {
            tree[idx] = val;
            return;
        }

        size_t mid = left_close + (right_open - left_close) / 2;
        if (i_src < mid) set(i_src, val, 2 * idx + 1, left_close, mid);
        else set(i_src, val, 2 * idx + 2, mid, right_open);
        tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void set(size_t i_src, T val) { set(i_src, val, 0, 0, size); }

    // increment value at index
    void increment(size_t left_src, size_t right_src, S val, size_t idx, size_t left_close, size_t right_open) {
        if (left_close >= right_src or left_src >= right_open) return;
        if (left_close >= left_src and right_open <= right_src) {
            tree[idx] = tree[idx] + val;
            if (right_open - left_close > 1)
                tree[idx].actual_len =
                    tree[idx].count ? tree[idx].length : tree[2 * idx + 1].actual_len + tree[2 * idx + 2].actual_len;
            return;
        }

        size_t mid = left_close + (right_open - left_close) / 2;
        increment(left_src, right_src, val, 2 * idx + 1, left_close, mid);
        increment(left_src, right_src, val, 2 * idx + 2, mid, right_open);
        tree[idx].actual_len =
            tree[idx].count ? tree[idx].length : tree[2 * idx + 1].actual_len + tree[2 * idx + 2].actual_len;
    }

    void increment(size_t left_src, size_t right_src, S val) { increment(left_src, right_src, val, 0, 0, size); }

    // query sum of range [left, right)
    S count(size_t left, size_t right, size_t idx, size_t left_close, size_t right_open) {
        if (left_close >= right or left >= right_open) return S{};
        if (left_close >= left and right_open <= right) return tree[idx].actual_len;

        // not fully covered
        if (tree[idx].count) {
            auto union_left = max(left, left_close);
            auto union_right = min(right, right_open);
            return len(union_left, union_right, idx, left_close, right_open);
        } else {
            size_t mid = left_close + (right_open - left_close) / 2;
            S left_val = count(left, right, 2 * idx + 1, left_close, mid);
            S right_val = count(left, right, 2 * idx + 2, mid, right_open);
            return left_val + right_val;
        }
    }

    S len(size_t left, size_t right, size_t idx, size_t left_close, size_t right_open) {
        if (left_close >= right or left >= right_open) return S{};
        if (left_close >= left and right_open <= right) return tree[idx].length;
        size_t mid = left_close + (right_open - left_close) / 2;
        S left_val = len(left, right, 2 * idx + 1, left_close, mid);
        S right_val = len(left, right, 2 * idx + 2, mid, right_open);
        return left_val + right_val;
    }
    S count(size_t left, size_t right) { return count(left, right, 0, 0, size); }

    S test() { return tree.front().actual_len; }
};

class Interval {
public:
    int length, count, actual_len;
    Interval operator+(const Interval &other) {
        Interval res;
        res.actual_len = actual_len + other.actual_len;
        res.count = min(count, other.count);
        return res;
    }
    Interval operator+(const int &val) {
        Interval res;
        res.length = length;
        res.count = count + val;
        res.actual_len = res.count ? length : 0;
        return res;
    }
};

int main() {
    size_t n, q;
    cin >> n;
    SegmentTree<Interval, int> intervals(--n);
    int pre;
    cin >> pre;
    for (size_t i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        intervals.set(i, Interval{cur - pre, 0, 0});
        pre = cur;
    }

    cin >> q;
    string cmd{};
    while (q--) {
        cin >> cmd;
        size_t left, right;
        switch (cmd.front()) {
        case 'i':
            cin >> left >> right;
            intervals.increment(left - 1, right - 1, 1);
            break;
        case 'd':
            cin >> left >> right;
            intervals.increment(left - 1, right - 1, -1);
            break;
        default:
            cin >> left >> right;
            cout << intervals.count(left - 1, right - 1) << endl;
            break;
        }
    }
}