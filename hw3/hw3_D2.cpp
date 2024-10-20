#include <bits/stdc++.h>
using namespace std;

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
        if (right_open - left_close == 1) return tree[idx].count ? tree[idx].length : 0;
        if (left_close >= right or left >= right_open) return S{};
        if (left_close >= left and right_open <= right and tree[idx].count) return tree[idx].length;

        // not fully covered
        size_t mid = left_close + (right_open - left_close) / 2;
        S left_val = count(left, right, 2 * idx + 1, left_close, mid);
        S right_val = count(left, right, 2 * idx + 2, mid, right_open);
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

struct Rectangle {
    int x1, y1, x2, y2;
};

struct Event {
    int x, y1, y2;
    bool is_start;
};

using IntPair = pair<int, int>;

int main() {
    // it's just like the previous one, and the sweep line determine the insertion and deletion of intervals
    size_t n;
    cin >> n;
    vector<Rectangle> rectangles(n);
    for (auto &i : rectangles) cin >> i.x1 >> i.y1 >> i.x2 >> i.y2;
    vector<Event> events;
    vector<IntPair> y;
    for (size_t i = 0; i < n; i++) {
        auto [x1, y1, x2, y2] = rectangles[i];
        y.emplace_back(y1, i);
        y.emplace_back(y2, i + n);
    }
    sort(y.begin(), y.end());
    SegmentTree<Interval, int> intervals(2 * n);
    auto y_unique = 0, prev_y = y.front().first;
    for (size_t i = 0; i < 2 * n; i++) {
        if (y[i].first != prev_y) {
            intervals.set(y_unique, Interval{y[i].first - prev_y, 0, 0});
            prev_y = y[i].first;
            y_unique++;
        }
        if (y[i].second < n) rectangles[y[i].second].y1 = y_unique;
        else rectangles[y[i].second - n].y2 = y_unique;
    }
    for (const auto &[x1, y1, x2, y2] : rectangles) {
        events.push_back(Event{x1, y1, y2, true});
        events.push_back(Event{x2, y1, y2, false});
    }
    sort(events.begin(), events.end(), [](Event &a, Event &b) { return a.x < b.x; });
    long long ans = 0;
    for (size_t i = 0, cur_x = events.front().x; i < 2 * n; i++) {
        auto [x, y1, y2, is_add] = events[i];
        auto union_len = intervals.test();
        auto dx = x - cur_x;
        ans += union_len * dx;
        cur_x = x;
        if (is_add) intervals.increment(y1, y2, 1);
        else intervals.increment(y1, y2, -1);
    }
    cout << ans << endl;
}