#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, int64_t> Point;

inline bool cross_product(const Point &a, const Point &b, const Point &c) {
    auto u_x = b.first - a.first, u_y = b.second - a.second;
    auto v_x = b.first - c.first, v_y = b.second - c.second;
    return u_x * v_y - u_y * v_x < 0;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<Point> convex(n), query(m);
    for (size_t i = 0; i < n; i++) cin >> convex[i].first >> convex[i].second;
    for (size_t i = 0; i < m; i++) cin >> query[i].first >> query[i].second;

    for (const auto &q : query)
        for (size_t i = 1; i < n - 1; i++)
            if (cross_product(convex[i - 1], convex[i], q) and cross_product(q, convex[i], convex[i + 1])) {
                cout << i + 1 << endl;
                break;
            }
}