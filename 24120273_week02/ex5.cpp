#include <iostream>
#include <string>
using namespace std;
int sumsubarray(int arr[],int n, int target){
    int sum;
    int minlength =n+1;
    int nowlength;
    int right=0,left =0;
    for (int right;right< n ;right++){
        sum=+ arr[right];
        while (target >= sum){
            nowlength = right-left+1;
        }
        if(minlength < nowlength){
            return minlength;
        }
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i=0 ;i<n;i++){
        cin>>arr[i];
    }
    for (int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    int target ;
    cin>> target;
    cout<<"Target: "<< target<<endl;
    sumsubarray(arr, n,target);
    cout << sumsubarray(arr, n , target ); 
    return 0;
}