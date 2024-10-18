#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n;
    cin >> n;
    auto base = 0LL, power = 0LL, result = 0LL;
    constexpr auto MOD = 1'000'000'007LL;
    while (n--) {
        cin >> base >> power;
        result = 1LL;
        while (power) {
            if (power & 1) result = result * base % MOD;
            base = base * base % MOD;
            power >>= 1;
        }
        cout << result << endl;
    }
}