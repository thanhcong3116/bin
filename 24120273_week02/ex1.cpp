#include<iostream>
using namespace std;
int linearsearch(int arr[],int n, int k){
    for(int i=0 ;i<n;i++){
        if(arr[i]==k){
            return i;
        }
    }
    return -1;
}
int main(){
    int n;
    cin>> n;
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
    cin >> k;
    cout<<endl;
    cout <<linearsearch(arr,n,k);
    return 0;
}
