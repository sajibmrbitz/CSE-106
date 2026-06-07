#include <iostream>
using namespace std;

class LinkedList{
private:
    class Node{
    public:
        int element;
        Node* next;
        Node* prev;
        
        Node(int val){
            this->element=val;
            this->next=nullptr;
            this->prev=nullptr;
        }
    };

    Node* head;
    Node* tail;
    Node* curr;
    int listsize;
    int current;

public:
    LinkedList(){
        head=nullptr;
        tail=nullptr;
        curr=nullptr;
        listsize=0;
        current=-1;
    }

    ~LinkedList(){
        clear();
    }

    void print(){
        cout<<"[ ";
        if(listsize==0){
            cout<<". ";
        } 
        else{
            Node* temp=head;
            while(temp!=nullptr){
                cout<<temp->element;
                if(temp==curr) cout<<"|";
                cout<<" ";
                temp=temp->next;
            }
        }
        cout<<"]"<<endl;
    }

    void insert_cur(int item){
        Node* newNode=new Node(item);

        if(listsize==0){
            head=tail=curr=newNode;
            current=0;
        } 
        else{
            newNode->prev=curr;
            newNode->next=curr->next;

            if(curr->next!=nullptr){
                curr->next->prev=newNode;
            } 
            else{
                tail=newNode;
            }
            curr->next=newNode;
            curr=newNode;
            current++;
        }
        listsize++;
    }

    int delete_cur(){
        if (listsize==0 || curr==nullptr) return -1;
        Node* tbd=curr;
        int val=tbd->element;

        if (tbd->prev!=nullptr) tbd->prev->next=tbd->next;
        else head=tbd->next;

        if (tbd->next!=nullptr) tbd->next->prev=tbd->prev;
        else tail=tbd->prev;

        if (tbd->next!=nullptr){
            curr=tbd->next;
        } 
        else{
            curr=tbd->prev;
            current--;
        }

        delete tbd;
        listsize--;
        if (listsize==0) current=-1;
        return val;
    }

    void append(int item){
        Node* newNode=new Node(item);

        if (listsize==0){
            head=tail=curr=newNode;
            current=0;
        } 
        else{
            newNode->prev=tail;
            tail->next=newNode;
            tail=newNode;
        }
        listsize++;
    }

    int size(){
        return listsize;
    }

    void prev(int n){
        if (listsize==0 || curr==nullptr) return;
        while (n>0 && curr->prev!=nullptr){
            curr=curr->prev;
            current--;
            n--;
        }
    }

    void next(int n){
        if (listsize==0 || curr==nullptr) return;
        while (n>0 && curr->next!=nullptr){
            curr=curr->next;
            current++;
            n--;
        }
    }

    int is_present(int n){
        Node* temp=head;
        while(temp!=nullptr){
            if (temp->element==n) return 1;
            temp=temp->next;
        }
        return 0;
    }

    void clear(){
        Node* temp=head;
        while(temp!=nullptr){
            Node* nextNode=temp->next;
            delete temp;
            temp=nextNode;
        }
        head=nullptr;
        tail=nullptr;
        curr=nullptr;
        listsize=0;
        current=-1;
    }

    int delete_item(int item){
        Node* temp=head;
        int idx=0;
        while(temp!=nullptr){
            if(temp->element==item){
                if(temp->prev) temp->prev->next=temp->next;
                else head=temp->next;

                if(temp->next) temp->next->prev=temp->prev;
                else tail=temp->prev;

                if(curr==temp){
                    if(temp->next) curr=temp->next;
                    else{
                        curr=temp->prev;
                        if(curr) current--;
                        else current=-1;
                    }
                } 
                else if (idx<current){
                    current--;
                }

                delete temp;
                listsize--;
                return 1;
            }
            temp=temp->next;
            idx++;
        }
        return -1;
    }

    void swap_ind(int ind1, int ind2){
        if(ind1==ind2) return;
        if(ind1<0 || ind1>=listsize || ind2<0 || ind2>=listsize) return;

        Node* n1=head;
        for(int i=0;i<ind1;i++){
            n1=n1->next;
        }

        Node* n2=head;
        for(int i=0;i<ind2;i++){
            n2=n2->next;
        }

        int temp=n1->element;
        n1->element=n2->element;
        n2->element=temp;
    }

    int search(int item){
        Node* temp=head;
        int idx=0;
        while(temp!=nullptr){
            if(temp->element==item) return idx;
            temp=temp->next;
            idx++;
        }
        return -1;
    }

    int find(int ind){
        if(ind<0 || ind>=listsize) return -1;
        Node* temp=head;
        for(int i=0;i<ind;i++){
            temp=temp->next;
        }
        return temp->element;
    }

    int update(int ind, int value){
        if(ind<0 || ind>=listsize) return -1;
        Node* temp=head;
        for(int i=0;i<ind;i++){
            temp=temp->next;
        }
        int old=temp->element;
        temp->element=value;
        return old;
    }

    int trim(){
        if(listsize==0) return -1;
        Node* tbd=tail;
        int val=tbd->element;

        if(curr==tbd){
            curr=tbd->prev;
            current--;
        }

        if (tbd->prev!=nullptr){
            tail=tbd->prev;
            tail->next=nullptr;
        } 
        else{
            head=nullptr;
            tail=nullptr;
            curr=nullptr;
        }

        delete tbd;
        listsize--;
        return val;
    }

    void reverse(){
        if(listsize<=1) return;
        Node* start=head;
        Node* end=tail;
        int f=0, l=listsize-1;
        while(f<l){
            int temp=start->element;
            start->element=end->element;
            end->element=temp;

            start=start->next;
            end=end->prev;
            f++;
            l--;
        }
    }
};