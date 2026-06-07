#include "queue.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    capacity=initial_capacity;
    data=new int[capacity];
    front_idx=-1;
    rear_idx=-1;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    delete[] data;
}

// Size implementation
int ArrayQueue::size() const
{
    if(front_idx==-1) return 0;
    if(rear_idx>=front_idx) return rear_idx-front_idx+1;
    return capacity-front_idx+rear_idx+1;         //circular case
}

// Enqueue implementation
void ArrayQueue::enqueue(int item)
{
    if(size()==capacity){
        resize(capacity*2);
    }

    if(front_idx==-1){
        front_idx=0;
        rear_idx=0;
    } 
    else{
        rear_idx=(rear_idx+1)%capacity;
    }
    data[rear_idx]=item;
}

// Dequeue implementation
int ArrayQueue::dequeue()
{
    if(empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }

    int item=data[front_idx];

    if(front_idx==rear_idx){
        front_idx=-1;
        rear_idx=-1;
    } 
    else{
        front_idx=(front_idx+1)%capacity;
    }

    int currentsize=size();
    if(currentsize>0 && currentsize*4<=capacity){
        int new_capacity=capacity/2;
        if (new_capacity>=2){
            resize(new_capacity);
        }
    }

    return item;
}

// Clear implementation
void ArrayQueue::clear()
{
    delete[] data;

    capacity=2; 
    data=new int[capacity];
    front_idx=-1;
    rear_idx=-1;
}

// Front implementation
int ArrayQueue::front() const
{
    if(empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }
    return data[front_idx];
}

// Back implementation
int ArrayQueue::back() const
{
    if(empty()){
        cout<<"Error : Queue is empty!"<<endl;
        return -1;
    }
    return data[rear_idx];
}

// Empty implementation
bool ArrayQueue::empty() const
{
    return front_idx==-1;
}

// Print implementation
string ArrayQueue::toString() const
{
    if(empty()) return "<>";
    
    string s="<";
    int item_count=size();

    for(int i=0;i<item_count;i++){
        int idx=(front_idx+i)%capacity;
        s+=to_string(data[idx]);
        if(i<item_count-1){
            s+=", ";
        }
    }
    s+=">";
    return s;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    int item_count=size();
    int* new_data=new int[new_capacity];
    for (int i=0;i<item_count;i++){
        int old_idx=(front_idx+i)%capacity;
        new_data[i]=data[old_idx];
    }

    delete[] data;
    data=new_data;
    capacity=new_capacity;

    if(item_count==0){
        front_idx=-1;
        rear_idx=-1;
    } 
    else{
        front_idx=0;
        rear_idx=item_count-1;
    }
}

int ArrayQueue::getCapacity() const
{
    return capacity;
}