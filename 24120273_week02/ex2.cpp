#include <iostream>
using namespace std;
int sentinellinearsearch (int arr[], int n, int k){
    int last = arr[n-1];
    arr[n-1]=k;
    int i=0;
    while(arr[i]!=k){
        i++;
    }
    arr[n-1]=last;
    if(i < n-1 || arr[n-1]==k){
        return i;
    }
    return -1;
}
int main() {
    int n;
    cin >> n ;
    int arr[n];
    cout<<"nhap mang co "<< n <<" so: ";
    for (int i=0 ;i<n ;i++){
        cin >> arr[i];
    }
    for (int i = 0;i<n;i++){
        cout <<arr[i] <<" ";
    }
    cout<<endl;
    int k; 
    cout<<"Target: ";
    cin >>k;
    cout << sentinellinearsearch (arr,n,k);
    return 0;
}