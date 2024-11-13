#include <bits/stdc++.h>
using namespace std;

vector<long long> matrices;
vector<vector<long long>> dp;
vector<vector<size_t>> split;

auto min_multiply(size_t, size_t) -> long long;
auto print_optimal_parens(size_t, size_t) -> void;

int main() {
    // read input
    size_t n;
    cin >> n;
    matrices.resize(n + 1);
    for (auto &i : matrices) cin >> i;

    // initialize dp table
    dp.resize(n, vector<long long>(n, numeric_limits<long long>::max()));
    for (size_t i = 0; i < n; i++) dp[i][i] = 0;
    split.resize(n, vector<size_t>(n));
    auto ans = min_multiply(0, n - 1);

    // output
    cout << ans << endl;
    print_optimal_parens(0, n - 1);
    cout << endl;
}

auto min_multiply(size_t l, size_t r) -> long long {
    if (dp[l][r] != numeric_limits<long long>::max()) return dp[l][r];
    if (l == r) return dp[l][r] = 0;

    auto ans = numeric_limits<long long>::max();
    for (size_t i = l; i < r; i++) {
        auto tmp = min_multiply(l, i) + min_multiply(i + 1, r) + matrices[l] * matrices[i + 1] * matrices[r + 1];
        if (tmp < ans) {
            ans = tmp;
            split[l][r] = i;
        }
    }
    return dp[l][r] = ans;
}

auto print_optimal_parens(size_t l, size_t r) -> void {
    if (l == r) cout << "(A" << l + 1 << ")";
    else {
        cout << "(";
        print_optimal_parens(l, split[l][r]);
        print_optimal_parens(split[l][r] + 1, r);
        cout << ")";
    }
}