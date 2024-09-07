#include <bits/stdc++.h>
using namespace std;

typedef array<int, 5> Student;

int main() {
    size_t n;
    cin >> n;
    vector<Student> students(n);
    for (auto &student : students)
        for (auto &score : student) cin >> score;
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        auto a_min = *min_element(a.begin(), a.end()), b_min = *min_element(b.begin(), b.end());
        if ((a_min < 90 && b_min >= 90) || (b_min < 90 && a_min >= 90)) return a_min > b_min;
        auto a_sum = reduce(a.begin(), a.end()), b_sum = reduce(b.begin(), b.end());
        if (a_sum != b_sum) return a_sum > b_sum;
        for (size_t i = 0; i < 5; i++)
            if (a[i] != b[i]) return a[i] > b[i];
        return true;
    });
    for (const auto &student : students) {
        for (const auto &grade : student) cout << grade << " ";
        cout << endl;
    }
}