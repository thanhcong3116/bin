#include <iostream>
#include <algorithm> 
using namespace std;

int main() {
    int n;
    cin >> n; 
    
    int nums[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i]; 
    }
    
    sort(nums, nums + n);
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1, right = n - 1;
        int target = -nums[i];
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum == target) {
                cout << nums[i] << " " << nums[left] << " " << nums[right] << endl;
                
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return 0;
}