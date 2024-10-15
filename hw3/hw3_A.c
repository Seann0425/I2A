// #include <stdio.h>

// int quick_select(int[], int, int, int);

// int A[10000000];

// int main() {
//     int n, k;
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++) scanf("%d", &A[i]);
//     scanf("%d", &k);

//     int value = quick_select(A, 0, n - 1, k);
//     printf("%d\n", value);

//     return 0;
// }

/* probID: W5-A-Quick-Select */

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int In_Place_Partition(int A[], int left, int right, int key) {
    swap(&A[key], &A[left]);

    int i = left + 1, j = right;

    while (i <= j) {
        while (i <= j && A[i] <= A[left]) i++;
        while (i <= j && A[j] > A[left]) j--;
        if (i < j) {
            swap(&A[i], &A[j]);
            i++;
            j--;
        }
    }
    swap(&A[left], &A[j]);
    return j;
}

int quick_select(int A[], int left, int right, int k) {
    if (left == right) return A[left];
    int pivot = In_Place_Partition(A, left, right, (left + right) / 2);
    int q = pivot - left + 1;
    if (q == k) return A[pivot];
    if (q < k) return quick_select(A, pivot + 1, right, k - q);
    return quick_select(A, left, pivot - 1, k);
}