#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n;
    cin >> n;
    const auto target = n * n / 2 + 1;
    for (size_t i = 1; i <= n; i++) {
        if (i * i < target) continue;
    }
}