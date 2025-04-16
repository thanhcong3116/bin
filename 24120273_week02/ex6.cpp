#include <iostream>
using namespace std;

int main() {
    int n, target;
    cin >> n; 
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; 
    }
    
    cin >> target; 
    
    int left = 0, right = n - 1;
    bool found = false;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            found = true;
            break;
        } else if (sum < target) {
            left++; 
        } else {
            right--; 
        }
    }
    
    cout << (found ? "YES" : "NO") << endl;
    return 0;
}