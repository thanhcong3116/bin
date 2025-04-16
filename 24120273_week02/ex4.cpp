#include <iostream>
using namespace std;

// Hàm tính tổng mảng
int sumArray(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

// Hàm tìm giá trị lớn nhất trong mảng
int findMax(int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Hàm kiểm tra có thể ship với capacity cho trước không
bool canShip(int weights[], int n, int days, int capacity) {
    int currentLoad = 0;
    int requiredDays = 1;
    
    for (int i = 0; i < n; i++) {
        if (currentLoad + weights[i] > capacity) {
            requiredDays++;
            currentLoad = 0;
        }
        currentLoad += weights[i];
    }
    
    return requiredDays <= days;
}

// Hàm đệ quy tìm kiếm nhị phân
int findMinCapacity(int weights[], int n, int days, int left, int right) {
    if (left >= right) {
        return left;
    }
    
    int mid = left + (right - left) / 2;
    
    if (canShip(weights, n, days, mid)) {
        return findMinCapacity(weights, n, days, left, mid);
    } else {
        return findMinCapacity(weights, n, days, mid + 1, right);
    }
}

int main() {
    int n;
    cin >> n;
    
    int weights[n];
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    
    int days;
    cin >> days;
    
    int left = findMax(weights, n);
    int right = sumArray(weights, n);
    
    int result = findMinCapacity(weights, n, days, left, right);
    cout << result << endl;
    
    return 0;
}