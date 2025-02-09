#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void quickSortFirstPivot(vector<int>& arr, int low, int high);
void quickSortMiddlePivot(vector<int>& arr, int low, int high);
void quickSortRandomPivot(vector<int>& arr, int low, int high);
void quickSortMedianPivot(vector<int>& arr, int low, int high);

int partitionFirst(vector<int>& arr, int low, int high);
int partitionMiddle(vector<int>& arr, int low, int high);
int partitionRandom(vector<int>& arr, int low, int high);
int partitionMedian(vector<int>& arr, int low, int high);

int median(vector<int> arr);

vector<int> generateRandomData(int size);
vector<int> generateSortedData(int size);
vector<int> generateReverseSortedData(int size);

int main() {
    srand(time(0));

    int sizes[] = { 10000, 20000, 30000, 40000, 50000 };

    for (int size : sizes) {
        cout << "Testing for size: " << size << endl;

        vector<int> randomData = generateRandomData(size);
        vector<int> sortedData = generateSortedData(size);
        vector<int> reverseData = generateReverseSortedData(size);

        vector<int> temp;

        cout << "First Element as Pivot:" << endl;
        temp = randomData;
        auto start = chrono::high_resolution_clock::now();
        quickSortFirstPivot(temp, 0, temp.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        cout << "Random Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        temp = sortedData;
        start = chrono::high_resolution_clock::now();
        quickSortFirstPivot(temp, 0, temp.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Sorted Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        temp = reverseData;
        start = chrono::high_resolution_clock::now();
        quickSortFirstPivot(temp, 0, temp.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Reverse Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        cout << "Middle Element as Pivot:" << endl;
        temp = randomData;
        start = chrono::high_resolution_clock::now();
        quickSortMiddlePivot(temp, 0, temp.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Random Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        cout << "Random Element as Pivot:" << endl;
        temp = randomData;
        start = chrono::high_resolution_clock::now();
        quickSortRandomPivot(temp, 0, temp.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Random Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        cout << "Median Element as Pivot:" << endl;
        temp = randomData;
        start = chrono::high_resolution_clock::now();
        quickSortMedianPivot(temp, 0, temp.size() - 1);
        end = chrono::high_resolution_clock::now();
        cout << "Random Data: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        cout << endl;
    }

    return 0;
}

void quickSortFirstPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionFirst(arr, low, high);
        quickSortFirstPivot(arr, low, pivotIndex - 1);
        quickSortFirstPivot(arr, pivotIndex + 1, high);
    }
}

int partitionFirst(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1;

    for (int j = low + 1; j <= high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[low], arr[i - 1]);
    return i - 1;
}

void quickSortMiddlePivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionMiddle(arr, low, high);
        quickSortMiddlePivot(arr, low, pivotIndex - 1);
        quickSortMiddlePivot(arr, pivotIndex + 1, high);
    }
}

int partitionMiddle(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[low]);
    return partitionFirst(arr, low, high);
}

void quickSortRandomPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandom(arr, low, high);
        quickSortRandomPivot(arr, low, pivotIndex - 1);
        quickSortRandomPivot(arr, pivotIndex + 1, high);
    }
}

int partitionRandom(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[low]);
    return partitionFirst(arr, low, high);
}

void quickSortMedianPivot(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionMedian(arr, low, high);
        quickSortMedianPivot(arr, low, pivotIndex - 1);
        quickSortMedianPivot(arr, pivotIndex + 1, high);
    }
}

int partitionMedian(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = median({ arr[low], arr[mid], arr[high] });
    if (pivot == arr[mid]) swap(arr[mid], arr[low]);
    else if (pivot == arr[high]) swap(arr[high], arr[low]);
    return partitionFirst(arr, low, high);
}

int median(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr[1];
}

vector<int> generateRandomData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) data[i] = rand() % 100000;
    return data;
}

vector<int> generateSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) data[i] = i;
    return data;
}

vector<int> generateReverseSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) data[i] = size - i;
    return data;
}
