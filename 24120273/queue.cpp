#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NODE{
    int key;
    NODE* p_next;
};
struct Queue {
    NODE* head;
    NODE* tail;
};
Queue* initializeQueue(){
    Queue* createnode = new Queue();
    createnode->head = nullptr;
    createnode->tail= nullptr;
    return createnode;       
}   
void enqueue(Queue &q, int key){
    NODE* node1= new NODE();
    node1->key= key;
    node1->p_next= nullptr;

    if(q.tail == nullptr){
        q.head = q.tail = node1;
        }else{
        q.tail->p_next = node1; 
        q.tail= node1;
    } 
}
int dequeue(Queue &q){
    if(q.head==nullptr){
        return -1;
    }
    NODE* temp = q.head;
    int val = q.head->key;
    q.head= q.head->p_next;

    if(q.head==nullptr){
        q.tail=nullptr;
    }
    delete temp;
    return val;
}
int size(Queue& q){
    int count=0;
    NODE* current = q.head;
    while(current != nullptr){
        count++;
        current = current->p_next;
    }
    return count;
}
bool isEmpty(Queue q){
    if(q.head == nullptr){
        return 1;
    }
        return false;
}

void process(Queue& q, const string& filename, const string& outfile){
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
            while (q.head!= nullptr){
                NODE* temp = q.head;
                q.head= q.head->p_next;
                delete temp;
            }
            Outfile << "EMPTY"<<endl;

        }else if(command== "enqueue"){
            int key;
            Infile >> key;
            enqueue(q,key);
            NODE* current = q.head;
            while(current != nullptr){
                Outfile << current->key <<endl;
                current = current->p_next;
            }
            
        }else if(command == "dequeue"){
             dequeue(q);
            if(isEmpty(q)){
                Outfile <<"EMPTY";
            }else{
                NODE* current= q.head;
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
int main() {
    int val;
    Queue* s= initializeQueue();
    
    process(*s,"D:\\24120273\\Input.txt","D:\\24120273\\Output.txt");

    delete s;
    return 0;
}