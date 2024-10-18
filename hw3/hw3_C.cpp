#include <bits/stdc++.h>
using namespace std;

constexpr auto MOD = 1'000'000'007LL;

class Matrix {
public:
    size_t row, col;
    vector<vector<long long>> elements;

    Matrix(size_t row, size_t col) : row(row), col(col) { elements.resize(row, vector<long long>(col, 0)); };

    Matrix &operator*=(const Matrix &other) {
        Matrix result(row, other.col);
        for (size_t i = 0; i < result.row; i++) {
            for (size_t j = 0; j < result.col; j++) {
                for (size_t k = 0; k < col; k++) {
                    result.elements[i][j] += elements[i][k] * other.elements[k][j] % MOD;
                    result.elements[i][j] %= MOD;
                }
            }
        }
        return (*this = result);
    }

    static auto element_sum(const Matrix &mat) -> long long {
        auto sum = 0LL;
        for (const auto &row : mat.elements)
            for (const auto &ele : row) sum = (sum + ele) % MOD;
        return sum;
    }
    static auto identity(size_t size) -> Matrix {
        Matrix i(size, size);
        for (size_t j = 0; j < size; j++) i.elements[j][j] = 1;
        return i;
    }
};

Matrix operator*(const Matrix &A, const Matrix &B) {
    Matrix result(A);
    return result *= B;
}

int main() {
    size_t str_size, opr_cnt, rank;
    string str{};
    cin >> str_size >> opr_cnt >> str >> rank;
    Matrix str_mat(rank, 1);
    Matrix transform(rank, rank);

    // initialize str_mat
    for (const auto &i : str) str_mat.elements[static_cast<size_t>(i - 'a')].front()++;
    // initialize transform
    for (size_t i = 0; i < rank; i++) {
        cin >> str;
        for (const auto &j : str) transform.elements[static_cast<size_t>(j - 'a')][i]++;
    }

    // fast matrix exponentiation
    Matrix result = Matrix::identity(rank);
    while (opr_cnt) {
        if (opr_cnt & 1) result *= transform;
        transform *= transform;
        opr_cnt >>= 1;
    }

    // print result
    cout << Matrix::element_sum(result * str_mat) << endl;
}