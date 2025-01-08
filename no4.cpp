/*
    Program Sorting Comparison: Radix, Quick, and Merge Sort
    Nama: Ridho Kurniawan
    NIM: 231011401209
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Radix Sort
void radixSort(vector<int>& arr) {
    int maxNum = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        vector<int> output(arr.size());
        int count[10] = {0};

        // Count occurrences
        for (int num : arr) count[(num / exp) % 10]++;

        // Accumulate counts
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];

        // Build output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[--count[digit]] = arr[i];
        }

        // Copy output to arr
        arr = output;
    }
}

// Quick Sort
vector<int> quickSort(const vector<int>& arr) {
    if (arr.size() <= 1) return arr;

    int pivot = arr[0];
    vector<int> less, equal, greater;

    for (int num : arr) {
        if (num < pivot) less.push_back(num);
        else if (num == pivot) equal.push_back(num);
        else greater.push_back(num);
    }

    vector<int> sortedLess = quickSort(less);
    vector<int> sortedGreater = quickSort(greater);

    sortedLess.insert(sortedLess.end(), equal.begin(), equal.end());
    sortedLess.insert(sortedLess.end(), sortedGreater.begin(), sortedGreater.end());
    return sortedLess;
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = left; k <= right; k++) arr[k] = temp[k - left];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Main Function
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    vector<int> arrRadix = arr;
    vector<int> arrQuick = arr;
    vector<int> arrMerge = arr;

    radixSort(arrRadix);
    cout << "Radix Sorted Array: ";
    for (int num : arrRadix) cout << num << " ";
    cout << "\n";

    vector<int> quickSorted = quickSort(arrQuick);
    cout << "Quick Sorted Array: ";
    for (int num : quickSorted) cout << num << " ";
    cout << "\n";

    mergeSort(arrMerge, 0, arrMerge.size() - 1);
    cout << "Merge Sorted Array: ";
    for (int num : arrMerge) cout << num << " ";
    cout << "\n";

    return 0;
}
