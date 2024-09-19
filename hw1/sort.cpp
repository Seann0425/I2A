#include <bits/stdc++.h>
using namespace std;

// in-place, stable, O(n^2)
void bubble_sort(vector<int> &arr) {
    if (arr.size() <= 1) return;
    const auto n = arr.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

// in-place, unstable, O(n^2)
void selection_sort(vector<int> &arr) {
    if (arr.size() <= 1) return;
    const auto n = arr.size();
    for (size_t i = 0; i < n; i++) {
        size_t minimum = i;
        for (size_t j = i + 1; j < n; j++) if (arr[j] < arr[minimum]) minimum = j;
        if (minimum != i) swap(arr[i], arr[minimum]);
    }
}

// stable, O(n^2)
void insertion_sort(vector<int> &arr) {
    const auto n = arr.size();
    for (size_t i = 1; i < n; i++) {
        int current_num = arr[i];
        size_t j = i;
        while (j - 1 < n and arr[j - 1] > current_num) {
            arr[j] = arr[j - 1];
            j--;
            arr[j] = current_num;
        }
    }
}

// merge sort
void merge_helper(vector<int> &arr, size_t left, size_t mid, size_t right) {
    vector<int> tmp(right - left + 1);
    size_t p = left, q = mid + 1, idx = 0;
    while (p <= mid and q <= right) {
        if (arr[p] < arr[q]) tmp[idx++] = arr[p++];
        else tmp[idx++] = arr[q++];
    }
    while (p <= mid) tmp[idx++] = arr[p++];
    while (q <= right) tmp[idx++] = arr[q++];
    for (idx = 0; idx < tmp.size(); idx++) arr[left + idx] = tmp[idx];
}

void merge_sort(vector<int> &arr, size_t left, size_t right) {
    if (left < right) {
        auto mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge_helper(arr, left, mid, right);
    }
}

// bucket sort, to be optimized
void bucket_sort(vector<int> &arr) {
    const auto n = arr.size();
    if (n <= 1) return;
    auto [mn, mx] = minmax_element(arr.begin(), arr.end());
    int shift = *mn, range = (*mx - *mn) / n;
    if (range == 0) range = 1;
    vector<vector<int>> buckets(n);
    for (const auto &num : arr) {
        int idx = (num - shift) / range;
        if (idx >= n) idx = n - 1;
        buckets[idx].push_back(num);
    }
    for (auto &bucket : buckets) sort(bucket.begin(), bucket.end());
    size_t i = 0;
    for (const auto &bucket : buckets) for (const auto &num : bucket) arr[i++] = num;
}

int main() {
    vector<int> arr;
    int input;
    while ((cin >> input) and !cin.eof()) arr.push_back(input);

    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // vector<int> bubble(arr);
    // start = chrono::high_resolution_clock::now();
    // bubble_sort(bubble);
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // cout << "Bubble Sort: ";
    // for (const auto &i : bubble) cout << i << " ";
    // cout << endl;
    // cout << "Cost: " << duration.count() << " microseconds" << endl;

    // vector<int> selection(arr);
    // start = chrono::high_resolution_clock::now();
    // selection_sort(selection);
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // cout << "Selection Sort: ";
    // for (const auto &i : selection) cout << i << " ";
    // cout << endl;
    // cout << "Cost: " << duration.count() << " microseconds" << endl;

    vector<int> insertion(arr);
    start = chrono::high_resolution_clock::now();
    insertion_sort(insertion);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Insertion Sort: ";
    // for (const auto &i : insertion) cout << i << " ";
    cout << endl;
    cout << "Cost: " << duration.count() << " microseconds" << endl;

    vector<int> merger(arr);
    start = chrono::high_resolution_clock::now();
    merge_sort(merger, 0, arr.size() - 1);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Merge Sort: ";
    // for (const auto &i : merger) cout << i << " ";
    cout << endl;
    cout << "Cost: " << duration.count() << " microseconds" << endl;

    vector<int> bucket(arr);
    start = chrono::high_resolution_clock::now();
    bucket_sort(bucket);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Bucket Sort: ";
    // for (const auto &i : bucket) cout << i << " ";
    cout << endl;
    cout << "Cost: " << duration.count() << " microseconds" << endl;

    // start = chrono::high_resolution_clock::now();
    // sort(arr.begin(), arr.end());
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // cout << "STL Sort: ";
    // for (const auto &i : arr) cout << i << " ";
    // cout << endl;
    // cout << "Cost: " << duration.count() << " microseconds" << endl;

    return 0;
}