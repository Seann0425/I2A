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

auto build_tree(size_t, const vector<int> &, const vector<size_t> &) -> TreeNode *; // build tree based on the array
auto search(TreeNode *, size_t &) -> unordered_set<int> *; // find the number of special segments of the root

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
    TreeNode *root = build_tree(n, nums, pos);
    search(root, ans);
    cout << ans << endl;
    return 0;
}

auto build_tree(size_t n, const vector<int> &nums, const vector<size_t> &pos) -> TreeNode * {
    // O(n)
    vector<int> left_side(n), right_side(n);
    vector<TreeNode *> node_pos(n);
    stack<int> monotonic;

    // left
    for (size_t i = 0; i < n; i++) {
        while (!monotonic.empty() and monotonic.top() < nums[i]) monotonic.pop();
        left_side[i] = monotonic.empty() ? numeric_limits<int>::max() : monotonic.top();
        monotonic.push(nums[i]);
    }

    // right
    monotonic = stack<int>();
    for (size_t i = n - 1; i < n; i--) {
        while (!monotonic.empty() and monotonic.top() < nums[i]) monotonic.pop();
        right_side[i] = monotonic.empty() ? numeric_limits<int>::max() : monotonic.top();
        monotonic.push(nums[i]);
    }

    // start building tree
    node_pos.back() = new TreeNode(static_cast<int>(n));
    for (size_t i = n - 1; i >= 1; i--)
        node_pos[i - 1] = (left_side[pos[i - 1]] < right_side[pos[i - 1]]
                               ? node_pos[left_side[pos[i - 1]] - 1]->right
                               : node_pos[right_side[pos[i - 1]] - 1]->left) = new TreeNode(static_cast<int>(i));

    return node_pos.back();
}

auto search(TreeNode *root, size_t &ans) -> unordered_set<int> * {
    // O(nlogn)
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