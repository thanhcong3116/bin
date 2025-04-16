#include <iostream>
#include <string>
using namespace std;
void generate(int n, string str){
 
    if(n==0){
        cout<<str<<endl;
    }else {
        generate(n-1, str +"0");
        generate(n-1, str +"1");
    }

}
int main (){
    int n;
    string str;
    cin>>n;
    cout<<"In ra day nhi phan: "<<endl;
    generate(n, str);
    return 0;
}