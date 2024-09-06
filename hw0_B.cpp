#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n;
    cin >> n;
    vector<int> nums(n);
    for (auto &num : nums) cin >> num;
    sort(nums.begin(), nums.end());
    for (const auto &num : nums) cout << num << " ";
}