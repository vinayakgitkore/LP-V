#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

// Sequential merge sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSortSequential(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortSequential(arr, left, mid);
    mergeSortSequential(arr, mid + 1, right);
    merge(arr, left, mid, right);
}




// Parallel merge sort
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
#pragma omp parallel sections
    {
#pragma omp section
        parallelMergeSort(arr, left, mid);
#pragma omp section
        parallelMergeSort(arr, mid + 1, right);
    }
    merge(arr, left, mid, right);
}
int main() {
    const int size = 10000;  // 1 million elements
    vector<int> data(size);

    // Generate random data
    srand(time(0));
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }

    // Make copies for sorting
    vector<int> sequentialData = data;
    vector<int> parallelData = data;

    // Sequential merge sort
    clock_t startSeq = clock();
    mergeSortSequential(sequentialData, 0, size - 1);
    clock_t endSeq = clock();
    double seqTime = double(endSeq - startSeq) / CLOCKS_PER_SEC;

    // Parallel merge sort
    clock_t startPar = clock();
    parallelMergeSort(parallelData, 0, size - 1);
    clock_t endPar = clock();
    double parTime = double(endPar - startPar) / CLOCKS_PER_SEC;

    // Check if sorting is correct
    bool sortedCorrectly = is_sorted(sequentialData.begin(), sequentialData.end());

    // Display results
    cout << "Sequential Merge Sort Time: " << seqTime << " seconds\n";
    cout << "Parallel Merge Sort Time: " << parTime << " seconds\n";
    cout << "Sorting Correctly: " << (sortedCorrectly ? "Yes" : "No") << endl;



}