#include <iostream>
using namespace std;
int factorial(int n){
    int sum = 1 ;
    for (int i=1;i<=n;i++){
        sum=sum*i;
    }
    cout<<sum<<endl;
    return sum;
}
int main(){
    int n;
    cout<<"Nhap so n bat kì : ";
    cin>> n;
    cout<<"Tong giai thua la: ";
    factorial(n);
    return 0;
}
