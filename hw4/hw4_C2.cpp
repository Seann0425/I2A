#include <bits/stdc++.h>
#include <ranges>
using namespace std;

using Event = tuple<int, int, int>; // start, end, point

vector<Event> events;
vector<size_t> previous;
vector<int> dp;

auto get_optimal(size_t) -> int;

int main() {
    // read input
    size_t n;
    cin >> n;
    events.resize(n);
    for (auto &[s, e, p] : events) cin >> s >> e >> p;

    // sort by end time
    sort(events.begin(), events.end(), [](const auto &a, const auto &b) { return get<1>(a) < get<1>(b); });

    // priority queue to find the previous non-overlapping event
    priority_queue<pair<int, size_t>> last_event;
    previous.resize(n, n); // n if no previous non-overlapping event
    for (size_t i = n - 1; i < n; i--) {
        const auto &[s, e, p] = events[i];
        while (!last_event.empty() && last_event.top().first > e) {
            previous[last_event.top().second] = i;
            last_event.pop();
        }
        last_event.emplace(s, i);
    }

    // dp
    dp.resize(n, 0);
    dp.front() = get<2>(events.front());
    for (size_t i = n - 1; i < n; i--) {
        auto [s, e, p] = events[i];
        dp[i] = max(get_optimal(i - 1), get_optimal(previous[i]) + p);
    }

    cout << dp.back() << endl;
}

auto get_optimal(size_t i) -> int {
    if (dp[i]) return dp[i];
    auto &point = get<2>(events[i]);
    return dp[i] = (i < dp.size() ? max(get_optimal(i - 1), get_optimal(previous[i]) + point) : point);
}