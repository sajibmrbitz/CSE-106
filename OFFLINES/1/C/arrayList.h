#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
    int current; 
} arrayList;

void init(arrayList* list){
    list->capacity=2;
    list->size=0;
    list->current=0;
    list->array=(int*) malloc(list->capacity*sizeof(int));
}

void free_list(arrayList* list){
    if(list->array!=NULL){
        free(list->array);
    }
    list->array=NULL;
    list->size=0;
    list->capacity=0;
}

void increase_capacity(arrayList* list){
    int oldcapacity=list->capacity;
    int newcapacity=oldcapacity*2;
    
    int* newArr=(int*)malloc(newcapacity*sizeof(int));
    
    for(int i=0;i<list->size;i++){
        newArr[i]=list->array[i];
    }
    
    free(list->array); 
    list->array=newArr;
    list->capacity=newcapacity;

    printf("Capacity doubled from %d to %d\n",oldcapacity,newcapacity);
}

void decrease_capacity(arrayList* list){
    if(list->capacity<=2) return; 

    int oldcapacity=list->capacity;
    int newcapacity=oldcapacity/2;
    int* newArr=(int*) malloc(newcapacity*sizeof(int));

    for(int i=0;i<list->size;i++){
        newArr[i]=list->array[i];
    }

    free(list->array);
    list->array=newArr;
    list->capacity=newcapacity;

    printf("Capacity halfed down from %d to %d\n",oldcapacity,newcapacity);
}

void print(arrayList* list){
    if(list->size==0){
        printf("[.]\n");
        return;
    }
    printf("[");
    for(int i=0;i<list->size;i++){
        printf("%d",list->array[i]);
        if(i==list->current) 
            printf("|"); 
        if(i<list->size-1) 
            printf(" ");
    }
    printf("]\n");
}

void insert(int item, arrayList* list){
    int insertIdx=0;
    if (list->size>0) {
        insertIdx=list->current+1; 
    }
    if(list->size*2>list->capacity){
        increase_capacity(list);
    }

    for(int i=list->size;i>insertIdx;i--){
        list->array[i]=list->array[i-1];
    }

    list->array[insertIdx]=item;
    list->current=insertIdx; 
    list->size++;
}

int delete_cur(arrayList* list){
    if(list->size==0 || list->current>=list->size) return -1;

    int tbdVal=list->array[list->current];

    for(int i=list->current;i<list->size-1;i++){
        list->array[i]=list->array[i+1];
    }
    list->size--;
    
    if(list->size*4<list->capacity){
        decrease_capacity(list);
    }
    return tbdVal;
}

void append(int item, arrayList* list){
    list->array[list->size]=item;
    list->size++;
    
    if(list->size*2>list->capacity){
        increase_capacity(list);
    }
}

int size(arrayList* list){
    return list->size;
}

void prev(int n, arrayList* list){
    list->current-=n;
    if (list->current<0) list->current=0;
}

void next(int n, arrayList* list){
    list->current+=n;
    if(list->current>list->size) 
        list->current=list->size;
}

int is_present(int n, arrayList* list){
    for(int i=0;i<list->size;i++){
        if(list->array[i]==n) return 1;
    }
    return 0;
}

void clear(arrayList* list){
    list->size=0;
    list->current=0;
    free(list->array);
    list->array=NULL;

    list->capacity=2; 
    list->array=(int*)malloc(list->capacity*sizeof(int));
}

int delete_item(int item, arrayList* list){
    int index=-1;
    for(int i=0;i<list->size;i++){
        if(list->array[i]==item){
            index=i;
            break;
        }
    }
    if(index==-1) return -1;

    for(int i=index;i<list->size-1;i++){
        list->array[i]=list->array[i+1];
    }
    list->size--;
    
    if(list->current>index) 
        list->current--;
    
    if(list->size*4<list->capacity){
        decrease_capacity(list);
    }
    return item;
}

void swap_ind(int ind1, int ind2, arrayList* list){
    if(ind1<0 || ind1>=list->size || ind2<0 || ind2>=list->size) return;
    int temp=list->array[ind1];
    list->array[ind1]=list->array[ind2];
    list->array[ind2]=temp;
}

int search(int item, arrayList* list){
    for(int i=0; i<list->size; i++){
        if(list->array[i]==item) return i;
    }
    return -1;
}

int find(int ind, arrayList* list){
    if(ind<0 || ind>=list->size) return -1;
    return list->array[ind];
}

int update(int ind, int value, arrayList* list){

    if(ind<0 || ind>=list->size) return -1;

    int old=list->array[ind];
    list->array[ind]=value;
    return old;
}

int trim(arrayList* list){
    if(list->size==0) return -1;
    int val=list->array[list->size-1];
    list->size--;

    if(list->current>list->size) list->current=list->size;

    if(list->size*4<list->capacity){
        decrease_capacity(list);
    }
    return val;
}

void reverse(arrayList* list){
    int f=0, l=list->size-1;
    while(f<l){
        int temp=list->array[f];
        list->array[f]=list->array[l];
        list->array[l]=temp;
        f++;
        l--;
    }
}