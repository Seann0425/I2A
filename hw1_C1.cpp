#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool vector_order(T x_u, T y_u, T x_v, T y_v) {
    auto order = x_u * y_v - y_u * x_v;
    if (!order) return x_u * x_u + y_u * y_u < x_v * x_v + y_v * y_v;
    return order > 0;
}

int main() {
    long long x_u, y_u, x_v, y_v;
    cin >> x_u >> y_u >> x_v >> y_v;
    cout << (vector_order(x_u, y_u, x_v, y_v) ? "true"s : "false"s);
}