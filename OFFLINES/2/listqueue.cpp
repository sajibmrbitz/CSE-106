#include "queue.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    front_node=nullptr;
    rear_node=nullptr;
    current_size=0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    clear();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    Node* new_node=new Node(item);
    if(empty()){
        front_node=new_node;
        rear_node=new_node;
    } 
    else {
        rear_node->next=new_node;
        rear_node=new_node;
    }
    current_size++;
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    if(empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }
    
    Node* temp=front_node;      
    int item=temp->data;
    
    front_node=front_node->next; 
    
    if(front_node==nullptr){  
        rear_node=nullptr;
    }
    
    delete temp;
    current_size--;
    return item;
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    while(!empty()){
        dequeue();
    }
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    return current_size;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    if (empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }
    return front_node->data;
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    if(empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }
    return rear_node->data;
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    return front_node==nullptr;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    if(empty()) return"<>";
    
    string s="<";
    Node* curr=front_node;
    while(curr!=nullptr){
        s+=to_string(curr->data);
        if(curr->next!=nullptr){
            s+=", ";
        }
        curr=curr->next;
    }
    s+=">";
    return s;
}