#include <bits/stdc++.h>
using namespace std;

typedef tuple<long long, long long, size_t> Coordinate;

int main() {
    size_t n, index = 1;
    long long x_ref, y_ref;
    cin >> n;
    vector<Coordinate> points(n);
    for (auto &point : points) {
        cin >> get<0>(point) >> get<1>(point);
        get<2>(point) = index++;
    }

    // find reference point
    tie(x_ref, y_ref, ignore) =
        *min_element(points.begin(), points.end(), [](const auto &a, const auto &b) {
            if (get<0>(a) == get<0>(b)) return get<1>(a) < get<1>(b);
            return get<0>(a) < get<0>(b);
        });
    for (auto &point : points) {
        get<0>(point) -= x_ref;
        get<1>(point) -= y_ref;
    }
    sort(points.begin(), points.end(), [](const auto &a, const auto &b) {
        auto &x_a = get<0>(a), &y_a = get<1>(a), &x_b = get<0>(b), &y_b = get<1>(b);
        auto order = x_a * y_b - y_a * x_b;
        if (!order) return x_a * x_a + y_a * y_a < x_b * x_b + y_b * y_b;
        return order > 0;
    });
    for (const auto &point : points) cout << get<2>(point) << " ";
}