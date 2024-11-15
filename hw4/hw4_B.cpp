#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    size_t size;
    vector<long long> tree;
    vector<long long> lazy_tag;
    const long long DEFAULT = 0;
public:
    SegmentTree(size_t n) {
        size = 1;
        while (size < n) size *= 2; // perfect binary tree
        tree.resize(2 * size - 1, DEFAULT);
        lazy_tag.resize(2 * size - 1, DEFAULT);
    }

    long long merge(long long a, long long b) { return a + b; }

    void build(vector<long long> &src, size_t idx, size_t left, size_t right) {
        if (left > right) return; // out of range
        if (left == right) {
            tree[idx] = src[left];
            return;
        }

        size_t mid = left + (right - left) / 2;
        build(src, 2 * idx + 1, left, mid);
        build(src, 2 * idx + 2, mid + 1, right);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void increment(size_t idx, size_t cur_left, size_t cur_right, size_t left, size_t right, long long val) {
        if (lazy_tag[idx]) {
            tree[idx] += lazy_tag[idx] * (cur_right - cur_left + 1);
            if (cur_left != cur_right) {
                lazy_tag[2 * idx + 1] += lazy_tag[idx];
                lazy_tag[2 * idx + 2] += lazy_tag[idx];
            }
            lazy_tag[idx] = 0;
        }
        if (cur_left > cur_right or cur_left > right or cur_right < left) return; // out of range
        if (cur_left >= left and cur_right <= right) {
            // fully covered
            tree[idx] += val * (cur_right - cur_left + 1);
            if (cur_left != cur_right) {
                lazy_tag[2 * idx + 1] += val;
                lazy_tag[2 * idx + 2] += val;
            }
            return;
        }
        size_t mid = cur_left + (cur_right - cur_left) / 2;
        increment(2 * idx + 1, cur_left, mid, left, right, val);
        increment(2 * idx + 2, mid + 1, cur_right, left, right, val);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    long long query_sum(size_t idx, size_t cur_left, size_t cur_right, size_t left, size_t right) {
        if (cur_left > cur_right or cur_left > right or cur_right < left) return 0;
        if (lazy_tag[idx]) {
            tree[idx] += lazy_tag[idx] * (cur_right - cur_left + 1);
            if (cur_left != cur_right) {
                lazy_tag[2 * idx + 1] += lazy_tag[idx];
                lazy_tag[2 * idx + 2] += lazy_tag[idx];
            }
            lazy_tag[idx] = 0;
        }
        if (cur_left >= left and cur_right <= right) return tree[idx];
        size_t mid = cur_left + (cur_right - cur_left) / 2;
        auto left_sum = query_sum(2 * idx + 1, cur_left, mid, left, right);
        auto right_sum = query_sum(2 * idx + 2, mid + 1, cur_right, left, right);
        return merge(left_sum, right_sum);
    }
};

int main() {
    size_t n, q;
    cin >> n >> q;
    SegmentTree seg_tree(n);
    vector<long long> arr(n);
    for (auto &i : arr) cin >> i;
    seg_tree.build(arr, 0, 0, n - 1);
    while (q--) {
        auto op = 0ll;
        size_t l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            long long val;
            cin >> val;
            seg_tree.increment(0, 0, n - 1, l - 1, r - 1, val);
        } else cout << seg_tree.query_sum(0, 0, n - 1, l - 1, r - 1) << '\n';
    }
}