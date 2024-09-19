#include <bits/stdc++.h>
using namespace std;

int main() {
    uint64_t n;
    cin >> n;
    decltype(n) low = 1, high = n * n, mid, le, target = (n * n + 1) / 2;
    while (low < high) {
        mid = (low + high) / 2;
        le = 0;
        for (decltype(n) i = 1; i <= n; i++) le += min(n, mid / i);
        if (le >= target) high = mid;
        else low = mid + 1;
    }
    cout << high << endl;
}