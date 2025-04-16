#include <iostream>
using namespace std;

// Hàm đệ quy tìm phần tử nhỏ nhất
int findMinRecursive(int arr[], int left, int right) {
    // Trường hợp chỉ có 1 phần tử
    if (left == right) {
        return arr[left];
    }
    
    // Trường hợp có 2 phần tử
    if (right - left == 1) {
        return min(arr[left], arr[right]);
    }
    
    // Nếu đoạn đã được sắp xếp
    if (arr[left] < arr[right]) {
        return arr[left];
    }
    
    int mid = left + (right - left) / 2;
    
    // Nếu phần tử giữa lớn hơn phần tử cuối
    if (arr[mid] > arr[right]) {
        return findMinRecursive(arr, mid + 1, right);
    }
    // Ngược lại
    else {
        return findMinRecursive(arr, left, mid);
    }
}

int main() {
    int n;
    cin >> n;
    
    int* arr = new int[n];
 
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int minElement = findMinRecursive(arr, 0, n - 1);
    cout << minElement << endl;
    
    delete[] arr;
    
    return 0;
}