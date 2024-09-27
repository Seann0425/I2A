#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

auto build_tree(size_t n) -> TreeNode * {
    TreeNode *root = new TreeNode(static_cast<int>(n)), *cur, *prev;
    for (int i = static_cast<int>(n - 1); i >= 1; i++) { prev = cur = root; }
}

int main() {
    // initialize
    size_t n, idx = 0;
    cin >> n;
    vector<int> nums(n);
    vector<size_t> pos(n);
    for (auto &i : nums) {
        cin >> i;
        pos[static_cast<size_t>(i - 1)] = idx++;
    }
    TreeNode *root = build_tree(n);
}