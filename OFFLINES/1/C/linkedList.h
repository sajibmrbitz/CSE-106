#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int element;
    struct node* next;
    struct node* prev;
}node;

typedef struct {
    node* head;
    node* tail;
    node* current; 
    int size;
} linkedList;

void init(linkedList* list){
    list->head=NULL;
    list->tail=NULL;
    list->current=NULL;
    list->size=0;
}

void free_list(linkedList* list){
    node* temp=list->head;
    while(temp!=NULL){
        node* nextNode=temp->next;
        free(temp); 
        temp=nextNode;
    }
    list->head=NULL;
    list->tail=NULL;
    list->current=NULL;
    list->size=0;
}

void print(linkedList* list){
    if(list->size==0){
        printf("[.]\n");
        return;
    }

    printf("[ ");
    node* temp=list->head;

    while(temp!=NULL){
        printf("%d", temp->element);
        if(temp==list->current) printf("|");
        if(temp->next!=NULL) printf(" ");
        temp=temp->next;
    }

    printf("]\n");
}

void insert(int item, linkedList* list){
    node* newNode=(node*)malloc(sizeof(node)); 
    newNode->element=item;

    if(list->size==0){
        newNode->next=NULL;
        newNode->prev=NULL;
        list->head=newNode;
        list->tail=newNode;
        list->current=newNode;
    }
    else{
        newNode->prev=list->current;
        newNode->next=list->current->next;

        if(list->current->next!=NULL){
            list->current->next->prev=newNode;
        } 
        else{
            list->tail = newNode;
        }
        
        list->current->next=newNode;
        list->current=newNode; 
    }
    list->size++;
}


int delete_cur(linkedList* list){
    if(list->size==0 || list->current==NULL) return -1;
    
    node* tbd=list->current;
    int val=tbd->element;
    
    if(tbd->prev!=NULL) tbd->prev->next=tbd->next;
    else list->head=tbd->next;

    if(tbd->next!=NULL) tbd->next->prev=tbd->prev;
    else list->tail=tbd->prev;

    if(tbd->next!=NULL){
        list->current=tbd->next;
    }
    else
    list->current=tbd->prev;

    free(tbd); 
    list->size--;
    return val;
}

void append(int item, linkedList* list){
    node* newNode=(node*)malloc(sizeof(node));
    newNode->element=item;
    newNode->next=NULL;
    
    if(list->size==0){
        newNode->prev=NULL;
        list->head=list->tail=list->current=newNode;
    } 
    else{
        newNode->prev=list->tail;
        list->tail->next=newNode;
        list->tail=newNode;
    }
    list->size++;
}

int size(linkedList* list){
    return list->size;
}

void prev(int n, linkedList* list){
    if(list->size==0 || list->current==NULL) return;

    while(n>0){
        if(list->current->prev!=NULL){
            list->current=list->current->prev;
            n--;
        } 
        else{
            break; 
        }
    }
}

void next(int n, linkedList* list){
    if(list->size==0 || list->current==NULL) return;

    while(n>0){
        if(list->current->next!=NULL){
            list->current=list->current->next;
            n--;
        } 
        else{
            break;
        }
    }
}

int is_present(int n, linkedList* list){
    node* temp=list->head;
    while(temp!=NULL){
        if(temp->element==n) return 1;
        temp=temp->next;
    }
    return 0;
}

void clear(linkedList* list){
    free_list(list);
}

int delete_item(int item, linkedList* list){
    node* temp=list->head;
    while(temp){
        if(temp->element==item){
            if(temp->prev) temp->prev->next=temp->next;
            else list->head=temp->next;
            
            if(temp->next) temp->next->prev=temp->prev;
            else list->tail=temp->prev;

            if(list->current==temp){
                if(temp->next!=NULL){
                    list->current=temp->next; 
                } 
                else{
                    list->current=temp->prev; 
                }
            }
            
            free(temp);
            list->size--;
            return 1; 
        }
        temp=temp->next;
    }
    return -1; 
}

void swap_ind(int ind1, int ind2, linkedList* list){
    if(ind1<0 || ind1>=list->size || ind2<0 || ind2>=list->size) return;
    if(ind1==ind2) return;

    node* n1=list->head;
    for(int i=0;i<ind1;i++){
        n1=n1->next;
    }
    
    node* n2=list->head;
    for(int i=0;i<ind2;i++){
        n2=n2->next;
    }
    
    int temp=n1->element;
    n1->element=n2->element;
    n2->element=temp;
}

int search(int item, linkedList* list){
    node* temp=list->head;
    int idx=0;
    while(temp!=NULL){
        if(temp->element==item) return idx;
        temp=temp->next;
        idx++;
    }
    return -1;
}

int find(int ind, linkedList* list){
    if(ind<0 || ind>=list->size) return -1;

    node* temp=list->head;
    for(int i=0;i<ind;i++){
        temp=temp->next;
    }
    
    return temp->element;
}

int update(int ind, int value, linkedList* list){
    if(ind<0 || ind>=list->size) return -1;

    node* temp=list->head;
    for(int i=0;i<ind;i++){
        temp=temp->next;
    }
    
    int old=temp->element;
    temp->element=value;
    return old;
}

int trim(linkedList* list){
    if(list->size==0) return -1; 
    
    node* tbd=list->tail;
    int val=tbd->element;
    
    if(list->current==tbd){
        list->current=tbd->prev; 
    }
    
    if(tbd->prev){
        list->tail=tbd->prev;
        list->tail->next=NULL;
    } 
    else{
        list->head=NULL;
        list->tail=NULL;
        list->current=NULL;
    }

    free(tbd);
    list->size--;
    return val;
}

void reverse(linkedList* list){
    if(list->size<=1) return;

    node* start=list->head;
    node* end=list->tail;
    int f=0; 
    int l=list->size-1;

    while (f<l){
        int temp=start->element;
        start->element=end->element;
        end->element=temp;

        start=start->next;
        end=end->prev;
        f++;
        l--;
    }
}