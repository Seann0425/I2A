#include <bits/stdc++.h>
using namespace std;

int main() {
    // read input
    size_t n;
    cin >> n;
    vector<pair<int, int>> events(n);
    for (auto &[s, e] : events) cin >> s >> e;

    // sort by end time
    sort(events.begin(), events.end(), [](const auto &a, const auto &b) { return a.second < b.second; });
    auto end = numeric_limits<int>::min();
    for (const auto &[s, e] : events) {
        if (s <= end) n--;
        else end = e;
    }

    cout << n << endl;
}