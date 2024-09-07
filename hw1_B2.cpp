#include <bits/stdc++.h>
using namespace std;

typedef array<int, 6> Student;

int main() {
    size_t n;
    cin >> n;
    vector<Student> students(n);
    int number = 0;
    for (auto &student : students) {
        for (size_t i = 0; i < 5; i++) cin >> student[i];
        student[5] = number++;
    }
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        auto a_min = *min_element(a.begin(), a.begin() + 5), b_min = *min_element(b.begin(), b.begin() + 5);
        if ((a_min < 90 && b_min >= 90) || (b_min < 90 && a_min >= 90)) return a_min > b_min;
        auto a_sum = reduce(a.begin(), a.begin() + 5), b_sum = reduce(b.begin(), b.begin() + 5);
        if (a_sum != b_sum) return a_sum > b_sum;
        for (size_t i = 0; i < 5; i++)
            if (a[i] != b[i]) return a[i] > b[i];
        return true;
    });
    vector<int> ans(n);
    for (size_t i = 0; i < n; i++) ans[static_cast<size_t>(students[i].back())] = static_cast<int>(i + 1);
    for (const auto &rank : ans) cout << rank << " ";
}