#include <stdio.h>

// void MergeSortedArrays(int[], int, int[], int, int[]);

// int A[200000], n;
// int B[200000], m;
// int C[400000];

// int main() {
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++) scanf("%d", &A[i]);
//     scanf("%d", &m);
//     for (int i = 0; i < m; i++) scanf("%d", &B[i]);

//     MergeSortedArrays(A, n, B, m, C);

//     for (int i = 0; i < n + m; i++) printf("%d ", C[i]);
//     printf("\n");

//     return 0;
// }

/* probID: W0-C-MergeSortedArrays */

void MergeSortedArrays(int A[], int n, int B[], int m, int C[]) {
    size_t i = 0, j = 0, N = (size_t)n, M = (size_t)m;
    size_t idx = 0;
    while (i < N && j < M) {
        if (A[i] < B[j]) C[idx++] = A[i++];
        else C[idx++] = B[j++];
    }
    while (i < N) C[idx++] = A[i++];
    while (j < M) C[idx++] = B[j++];
}