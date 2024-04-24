#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, then the array is sorted
        if (!swapped)
            break;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "Sequential Bubble Sort Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, then the array is sorted
        if (!swapped)
            break;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "Parallel Bubble Sort Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

int main() {
    vector<int> arr = {64, 25, 12, 12, 11};

    cout << "Original array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // Sequential Bubble Sort
    vector<int> arrSequential = arr;
    sequentialBubbleSort(arrSequential);

    // Parallel Bubble Sort
    vector<int> arrParallel = arr;
    parallelBubbleSort(arrParallel);

    cout << "Sequential Sorted array: ";
    for (int x : arrSequential) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Parallel Sorted array: ";
    for (int x : arrParallel) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}