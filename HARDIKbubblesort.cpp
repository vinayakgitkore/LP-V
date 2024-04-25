#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <algorithm>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

int main() {
    const int size = 10000;  // 10,000 elements
    vector<int> data(size);

    // Generate random data
    srand(time(0));
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }

    // Make copies for sorting
    vector<int> sequentialData = data;
    vector<int> parallelData = data;

    // Sequential bubble sort
    clock_t startSeq = clock();
    bubbleSort(sequentialData);
    clock_t endSeq = clock();
    double seqTime = double(endSeq - startSeq) / CLOCKS_PER_SEC;

    // Parallel bubble sort
    clock_t startPar = clock();
    parallelBubbleSort(parallelData);
    clock_t endPar = clock();
    double parTime = double(endPar - startPar) / CLOCKS_PER_SEC;

    // Check if sorting is correct
bool sortedCorrectly = is_sorted(sequentialData.begin(), sequentialData.end());
    // Display results
    cout << "Sequential Bubble Sort Time: " << seqTime << " seconds\n";
    cout << "Parallel Bubble Sort Time: " << parTime << " seconds\n";
    cout << "Sorting Correctly: " << (sortedCorrectly ? "Yes" : "No") << endl;

    

    return 0;
}