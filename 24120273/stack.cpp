#include<iostream>
#include <fstream>
#include <string>

using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};
struct Stack
{
    NODE* top;
};
Stack *init()
{
    Stack *node1 = new Stack();
    node1->top = nullptr;
    return node1;
}
void push(Stack &s, int key)
{
    NODE *node2 = new NODE();
    node2->key= key;
    node2->p_next= s.top;
    s.top= node2;
}
int pop(Stack &s) {

    if(s.top == nullptr){
        return -1;
    }else{
        int bien = s.top->key;
        NODE* temp = s.top; 
        s.top= s.top->p_next;
        delete temp;
        return bien;
    }
}
int size(Stack& s) {
    int count = 0;
    NODE* current= s.top;
    while(current != nullptr){
        count++;
        current = current->p_next;
    }
    return count;
}
bool isEmpty(Stack s) {
    if(s.top == nullptr){
        return 1;
    }
    return false;
}
void process(Stack& s, const string& filename, const string& outfile){
    string command; 
    ifstream Infile(filename);
    ofstream Outfile(outfile);
    if(!Infile){
        cout<<"Khong the mo file Input.txt "<<endl;
        return;
    }
    if(!Outfile){
        cout<<"Khong the mo file Output.txt"<<endl;
        return;
    }
        while(Infile >> command)
      {
        if(command == "init"){

            while (s.top != nullptr){
                NODE* temp = s.top;
                s.top= s.top->p_next;
                delete temp;                      
            }
            Outfile << "EMPTY"<<endl;

        }else if(command== "push"){
            int key;
            Infile >> key;
            push(s,key);

            NODE* current = s.top;
            while(current != nullptr){
                Outfile << current->key <<endl;
                current = current->p_next;
            }
            
        }else if(command == "pop"){
             pop(s);
            if(isEmpty(s)){
                Outfile <<"EMPTY";
            }else{
                NODE* current= s.top;
                while (current !=nullptr){
                    Outfile<< current->key <<endl;
                    current= current->p_next;
                }                
            }
        }
    }

    Infile.close();
    Outfile.close();
}
int main(){
    Stack* s = init();
    
    process(*s,"D:\\24120273\\Input.txt","D:\\24120273\\Output.txt");

    delete s;

    return 0;
}