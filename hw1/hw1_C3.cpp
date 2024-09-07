#include <bits/stdc++.h>
using namespace std;

typedef tuple<long long, long long, size_t> Point;

bool non_convex(stack<Point> &hull, Point &next) {
    auto cur = hull.top();
    hull.pop();
    auto u_x = get<0>(cur) - get<0>(hull.top()), u_y = get<1>(cur) - get<1>(hull.top());
    auto v_x = get<0>(next) - get<0>(cur), v_y = get<1>(next) - get<1>(cur);
    hull.push(cur);
    auto order = u_x * v_y - u_y * v_x;
    return order <= 0;
}

int main() {
    size_t n, index = 1;
    cin >> n;
    vector<Point> points(n);
    for (auto &point : points) {
        cin >> get<0>(point) >> get<1>(point);
        get<2>(point) = index++;
    }

    // choose reference point
    auto [x_ref, y_ref, ignore] =
        *min_element(points.begin(), points.end(), [](const auto &a, const auto &b) {
            if (get<0>(a) == get<0>(b)) return get<1>(a) < get<1>(b);
            return get<0>(a) < get<0>(b);
        });

    // sort
    sort(points.begin(), points.end(), [&x_ref, &y_ref](const auto &a, const auto &b) {
        auto x_a = get<0>(a) - x_ref, y_a = get<1>(a) - y_ref;
        auto x_b = get<0>(b) - x_ref, y_b = get<1>(b) - y_ref;
        auto order = x_a * y_b - y_a * x_b;
        if (!order) return x_a * x_a + y_a * y_a < x_b * x_b + y_b * y_b;
        return order > 0;
    });

    // choose convex hull
    stack<Point> convex_hull;
    for (size_t i = 0; i < 3; i++) convex_hull.push(points[i]);
    for (size_t i = 3; i < n; i++) {
        while (convex_hull.size() > 1 && non_convex(convex_hull, points[i])) convex_hull.pop();
        convex_hull.push(points[i]);
    }
    convex_hull.push(points.front());

    // output
    cout << convex_hull.size() << endl;
    while (!convex_hull.empty()) {
        cout << get<2>(convex_hull.top()) << " ";
        convex_hull.pop();
    }
}