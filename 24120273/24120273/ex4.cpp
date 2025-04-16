#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
if (n == 1) {

 cout<<" Movedisk1from "<<from_rod<<" to "<<to_rod<<endl;
 return;
}
towerOfHanoi(n-1,from_rod,aux_rod,to_rod);
cout<<"Movedisk "<<n<< " from "<<from_rod<<" to "<<to_rod<<endl;
towerOfHanoi(n-1,aux_rod, to_rod,from_rod);
}
int main() {
int n=3;
towerOfHanoi(n,'A','C','B');
return 0;
}