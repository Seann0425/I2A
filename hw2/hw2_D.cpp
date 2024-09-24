#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n, ans{}, pos{};
    cin >> n;
    vector<size_t> left_side(n), right_side(n), position(n + 1);
    vector<int> nums(n);
    stack<size_t> monotonic;
    // input and record position and left side
    for (size_t i = 0; i < n; i++) {
        cin >> nums[i];
        position[static_cast<size_t>(nums[i])] = pos++;
        while (!monotonic.empty() and nums[monotonic.top()] < nums[i]) monotonic.pop();
        left_side[i] = monotonic.empty() ? numeric_limits<size_t>::max() : monotonic.top();
        monotonic.push(i);
    }
    // right side
    monotonic = stack<size_t>();
    for (size_t i = n - 1; i < n; i--) {
        while (!monotonic.empty() and nums[monotonic.top()] < nums[i]) monotonic.pop();
        right_side[i] = monotonic.empty() ? numeric_limits<size_t>::max() : monotonic.top();
        monotonic.push(i);
    }
    // choose the maximum number
    for (size_t i = n; i >= 3; i--) {
        unordered_set<int> two_sum;
        auto left = left_side[position[i]] < n ? left_side[position[i]] + 1 : 0;
        auto right = right_side[position[i]] < n ? right_side[position[i]] - 1 : n - 1;
        for (size_t j = left; j < position[i]; j++) two_sum.insert(i - nums[j]);
        for (size_t j = position[i] + 1; j <= right; j++) {
            if (two_sum.empty()) break;
            if (two_sum.count(nums[j])) {
                ans++;
                two_sum.erase(nums[j]);
            }
        }
    }
    cout << ans << endl;
}