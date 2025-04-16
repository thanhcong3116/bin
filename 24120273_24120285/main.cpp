#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int* readInput(const string& inputFile, int& n) {
    ifstream inFile(inputFile);
    int* arr = nullptr;
    if (inFile.is_open()) {
        inFile >> n;
        arr = new int[n];
        for (int i = 0; i < n; ++i) {
            inFile >> arr[i];
        }
        inFile.close();
    }
    return arr;
}

void writeOutput(const string& outputFile, int* arr, int n) {
    ofstream outFile(outputFile);
    if (outFile.is_open()) {
        outFile << n << endl;
        for (int i = 0; i < n; ++i) {
            outFile << arr[i] << " ";
        }
        outFile << endl;
        outFile.close();
    }
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void shakerSort(int* arr, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
        right--;
        for (int i = right; i > left; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
            }
        }
        left++;
    }
}

void shellSort(int* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) {
        arr[k++] = L[i++];
    }
    
    while (j < n2) {
        arr[k++] = R[j++];
    }
    
    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countingSort(int* arr, int n) {
    if (n == 0) return;
    
    int max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    int* count = new int[max_val + 1]();
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }
    
    int idx = 0;
    for (int i = 0; i <= max_val; ++i) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
    
    delete[] count;
}

void radixSort(int* arr, int n) {
    if (n == 0) return;
    
    int max_val = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        int* output = new int[n];
        int count[10] = {0};
        
        for (int i = 0; i < n; ++i) {
            count[(arr[i] / exp) % 10]++;
        }
        
        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }
        
        for (int i = n - 1; i >= 0; --i) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        for (int i = 0; i < n; ++i) {
            arr[i] = output[i];
        }
        
        delete[] output;
    }
}

void flashSort(int* arr, int n) {
    if (n == 0) return;
    
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    if (minVal == maxVal) return;

    int m = int(0.45 * n);
    if (m <= 1) m = 2;
    int* L = new int[m + 1]();

    double c = (double)(m - 1) / (maxVal - minVal);
    for (int i = 0; i < n; ++i) {
        int k = int(c * (arr[i] - minVal));
        L[k + 1]++;
    }
    
    for (int i = 1; i <= m; ++i) {
        L[i] += L[i - 1];
    }

    int move = 0, j = 0, k = m - 1;
    while (move < n - 1) {
        while (j >= L[k]) {
            j++;
            k = int(c * (arr[j] - minVal));
        }
        int flash = arr[j];
        while (j < L[k]) {
            k = int(c * (flash - minVal));
            int idx = --L[k];
            swap(flash, arr[idx]);
            move++;
        }
    }

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    
    delete[] L;
}

int main(int argc, char* argv[]) {
    string algorithm, inputFile, outputFile;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            algorithm = argv[++i];
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            inputFile = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }

    if (algorithm.empty() || inputFile.empty() || outputFile.empty()) {
        return 1;
    }

    int n;
    int* arr = readInput(inputFile, n);
    
    transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);
    if (algorithm == "selection-sort") {
        selectionSort(arr, n);
    }
    else if (algorithm == "insertion-sort") {
        insertionSort(arr, n);
    }
    else if (algorithm == "bubble-sort") {
        bubbleSort(arr, n);
    }
    else if (algorithm == "shaker-sort") {
        shakerSort(arr, n);
    }
    else if (algorithm == "shell-sort") {
        shellSort(arr, n);
    }
    else if (algorithm == "heap-sort") {
        heapSort(arr, n);
    }
    else if (algorithm == "merge-sort") {
        mergeSort(arr, 0, n - 1);
    }
    else if (algorithm == "quick-sort") {
        quickSort(arr, 0, n - 1);
    }
    else if (algorithm == "counting-sort") {
        countingSort(arr, n);
    }
    else if (algorithm == "radix-sort") {
        radixSort(arr, n);
    }
    else if (algorithm == "flash-sort") {
        flashSort(arr, n);
    }
    else {
        delete[] arr;
        return 1;
    }
    
    writeOutput(outputFile, arr, n);
    delete[] arr;
    
    return 0;
}