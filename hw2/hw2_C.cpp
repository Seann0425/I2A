#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, int64_t> Point;
typedef tuple<Point, Point, Point> Vec;

auto cross_product(const Point &u, const Point &v) -> int {
    auto direc = u.first * v.second - u.second * v.first;
    if (direc > 0) return 1;
    if (direc < 0) return -1;
    return 0;
}

void build(Point &prev, Vec &cur, Point &next) {
    get<0>(cur).first = get<2>(cur).first - prev.first;
    get<0>(cur).second = get<2>(cur).second - prev.second;
    get<1>(cur).first = next.first - get<2>(cur).first;
    get<1>(cur).second = next.second - get<2>(cur).second;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<Point> queries(m);
    vector<Vec> convex(n - 1);
    Point origin;
    cin >> origin.first >> origin.second;
    for (size_t i = 0; i < n - 1; i++) cin >> get<2>(convex[i]).first >> get<2>(convex[i]).second;
    build(origin, convex.front(), get<2>(convex[1]));
    for (size_t i = 1; i < n - 2; i++) build(get<2>(convex[i - 1]), convex[i], get<2>(convex[i + 1]));
    build(get<2>(convex[n - 3]), convex[n - 2], origin);
    for (size_t i = 0; i < m; i++) cin >> queries[i].first >> queries[i].second;

    for (const auto &query : queries)
        cout << (lower_bound(convex.begin(), convex.end(), query,
                             [](const auto &vec, const auto &q) {
                                 Point v(get<2>(vec).first - q.first, get<2>(vec).second - q.second);
                                 auto direc_1 = cross_product(get<0>(vec), v);
                                 auto direc_2 = cross_product(v, get<1>(vec));
                                 return direc_1 < 0 and direc_2 > 0;
                             }) -
                 convex.begin()) +
                    2
             << endl;
}