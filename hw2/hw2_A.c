#include <stdio.h>

// void quick_sort(int[], int);

// int A[200000], n;

// int main() {
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++) scanf("%d", &A[i]);

//     quick_sort(A, n);

//     for (int i = 0; i < n; i++) printf("%d ", A[i]);
//     printf("\n");

//     return 0;
// }

/* probID: W3-A-QuickSort */

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int A[], int left, int right) {
    int pivot = A[right], i = left;
    for (int j = left; j < right; j++)
        if (A[j] < pivot) swap(&A[i++], &A[j]);
    swap(&A[i], &A[right]);
    return i;
}

void q_sort(int A[], int left, int right, int n) {
    if (left < right && right < n) {
        int pivot = partition(A, left, right);
        q_sort(A, left, pivot - 1, n);
        q_sort(A, pivot + 1, right, n);
    }
}

void quick_sort(int A[], int n) { q_sort(A, 0, n - 1, n); }