#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

vector<int> generateSortedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

vector<int> generateReverseArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortReduced(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void bubbleSortWithFlag(vector<int>& arr) {
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void bubbleSortTwoWay(vector<int>& arr) {
    bool swapped = true;
    size_t start = 0, end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        for (size_t i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        --end;

        for (size_t i = end; i > start; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++start;
    }
}

void measureSortingTime(void (*sortFunction)(vector<int>&), vector<int>& arr, const string& description) {
    auto start = chrono::high_resolution_clock::now();
    sortFunction(arr);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << setw(25) << description << " : " << elapsed.count() << " seconds" << endl;
}

int main() {
    srand(time(0));

    vector<int> sizes = { 5000, 10000, 20000, 30000, 40000, 50000, 60000 };

    for (int size : sizes) {
        cout << "\nTesting for array size: " << size << endl;

        vector<int> randomArray = generateRandomArray(size);
        vector<int> sortedArray = generateSortedArray(size);
        vector<int> reverseArray = generateReverseArray(size);

        cout << "Bubble Sort Times:\n";
        measureSortingTime(bubbleSort, randomArray, "Random Elements");
        measureSortingTime(bubbleSort, sortedArray, "Already Sorted");
        measureSortingTime(bubbleSort, reverseArray, "Reverse Sorted");

        cout << "\nBubble Sort Reduced Times:\n";
        measureSortingTime(bubbleSortReduced, randomArray, "Random Elements");
        measureSortingTime(bubbleSortReduced, sortedArray, "Already Sorted");
        measureSortingTime(bubbleSortReduced, reverseArray, "Reverse Sorted");

        cout << "\nBubble Sort With Flag Times:\n";
        measureSortingTime(bubbleSortWithFlag, randomArray, "Random Elements");
        measureSortingTime(bubbleSortWithFlag, sortedArray, "Already Sorted");
        measureSortingTime(bubbleSortWithFlag, reverseArray, "Reverse Sorted");

        cout << "\nBubble Sort Two Way Times:\n";
        measureSortingTime(bubbleSortTwoWay, randomArray, "Random Elements");
        measureSortingTime(bubbleSortTwoWay, sortedArray, "Already Sorted");
        measureSortingTime(bubbleSortTwoWay, reverseArray, "Reverse Sorted");
    }

    return 0;
}
