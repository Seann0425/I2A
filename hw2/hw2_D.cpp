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

auto build_tree(size_t, const vector<size_t> &) -> TreeNode *; // build tree based on the array
auto search(TreeNode *, size_t &) -> unordered_set<int> *;     // find the number of special segments of the root

int main() {
    // initialize
    size_t n, idx = 0, ans{};
    cin >> n;
    vector<int> nums(n);
    vector<size_t> pos(n);
    for (auto &i : nums) {
        cin >> i;
        pos[static_cast<size_t>(i - 1)] = idx++;
    }
    TreeNode *root = build_tree(n, pos);
    search(root, ans);
    cout << ans << endl;
    return 0;
}

auto build_tree(size_t n, const vector<size_t> &pos) -> TreeNode * {
    TreeNode *root = new TreeNode(static_cast<int>(n)), *cur, *prev;
    for (size_t i = n - 1; i >= 1; i--) {
        prev = cur = root;
        while (cur) {
            prev = cur;
            if (pos[i - 1] > pos[static_cast<size_t>(cur->val - 1)]) cur = cur->right;
            else cur = cur->left;
        }
        (pos[i - 1] > pos[static_cast<size_t>(prev->val - 1)] ? prev->right : prev->left) =
            new TreeNode(static_cast<int>(i));
    }
    return root;
}

auto search(TreeNode *root, size_t &ans) -> unordered_set<int> * {
    if (!root) {
        unordered_set<int> *leaf = new unordered_set<int>();
        return leaf;
    }
    auto minimum = search(root->left, ans), maximum = search(root->right, ans);
    if (minimum->size() > maximum->size()) swap(minimum, maximum);
    for (const auto &i : *minimum)
        if (maximum->count(root->val - i)) ans++;
    maximum->insert(minimum->begin(), minimum->end());
    maximum->insert(root->val);
    return maximum;
}