#include <iostream>
using namespace std;

class ArrayList{
private:
    int *array;
    int listsize;
    int capacity;
    int curr; 

    void increase_capacity(){
        int oldCap=capacity;
        capacity*=2;
        int *newArr=new int[capacity];

        for(int i=0;i<listsize;i++){
            newArr[i]=array[i];
        }

        delete[] array;
        array=newArr;
        cout<<"Capacity increased from "<<oldCap<<" to "<<capacity<<endl;
    }

    void decrease_capacity(){
        if(capacity<=2) return;
        int oldCap=capacity;
        capacity/=2;
        int *newArr=new int[capacity];

        for(int i=0;i<listsize;i++){
            newArr[i]=array[i];
        }

        delete[] array;
        array=newArr;
        cout<<"Capacity decreased from "<<oldCap<<" to "<<capacity<<endl;
    }

public:
    ArrayList(){
        capacity=2;
        listsize=0;
        curr=-1;
        array=new int[capacity];
    }

    ~ArrayList(){
        if(array){
            delete[] array;
        }
    }

    void print(){
        cout<<"[ ";
        if (listsize==0){
            cout<<". ";
        } 
        else{
            for(int i=0;i<listsize;i++){
                cout<<array[i];
                if(i==curr) cout<<"|";
                cout<<" ";
            }
        }
        cout<<"]"<<endl;
    }

    void insert_cur(int item){
        int insertIdx=0;
        if(listsize>0){
            insertIdx=curr+1;
        }
        if (listsize*2>=capacity){
            increase_capacity();
        }

        for(int i=listsize;i>insertIdx;i--){
            array[i]=array[i-1];
        }

        array[insertIdx]=item;
        curr=insertIdx;
        listsize++;
    }

    int delete_cur(){
        if(listsize==0) return -1;

        int deletedVal=array[curr];

        for(int i=curr;i<listsize-1;i++){
            array[i]=array[i+1];
        }

        listsize--;

        if(curr>=listsize && listsize>0){
            curr=listsize-1;
        }
        if(listsize==0) curr=-1;

        if (capacity>2 && listsize*4<capacity){
            decrease_capacity();
        }

        return deletedVal;
    }

    void append(int item){
        if(listsize>=capacity/2){
            increase_capacity();
        }
        array[listsize]=item;
        listsize++;
        if(listsize==1) curr=0;
    }

    int size(){
        return listsize;
    }

    void prev(int n){
        if(listsize==0) return;
        curr-=n;
        if(curr<0) curr=0;
    }

    void next(int n){
        if(listsize==0) return;
        curr+=n;
        if(curr>=listsize) curr=listsize-1;
    }

    int is_present(int n){
        for(int i=0;i<listsize;i++){
            if(array[i]==n) return 1;
        }
        return 0;
    }

    void clear(){
        listsize=0;
        curr=-1;
        delete[] array;
        capacity=2;
        array=new int[capacity];
    }

    int delete_item(int item){
        int index=-1;
        for(int i=0; i<listsize;i++){
            if(array[i]==item){
                index=i;
                break;
            }
        }

        if(index==-1) return -1;

        for(int i=index;i<listsize-1;i++){
            array[i]=array[i+1];
        }

        if(index<curr) curr--;
        else if(index==curr && curr==listsize-1) curr--;

        listsize--;
        if(listsize==0) curr=-1;

        if(capacity>2 && listsize*4<capacity){
            decrease_capacity();
        }

        return 1; 
    }

    void swap_ind(int ind1, int ind2){
        if(ind1==ind2) return;
        if(ind1<0 || ind1>=listsize || ind2<0 || ind2>=listsize) return;
        
        int temp=array[ind1];
        array[ind1]=array[ind2];
        array[ind2]=temp;
    }

    int search(int item){
        for(int i=0;i<listsize;i++){
            if(array[i]==item) return i;
        }
        return -1;
    }

    int find(int ind){
        if(ind<0 || ind>=listsize) return -1;
        return array[ind];
    }

    int update(int ind, int value){
        if(ind<0 || ind>=listsize) return -1;
        int old=array[ind];
        array[ind]=value;
        return old;
    }

    int trim(){
        if (listsize==0) return -1;
        int lastVal=array[listsize-1];
        listsize--;

        if(curr>=listsize) curr=listsize-1;
        if(listsize==0) curr=-1;

        if(capacity>2 && listsize*4<capacity){
            decrease_capacity();
        }
        return lastVal;
    }

    void reverse(){
        int f=0,l=listsize-1;
        while(f<l){
            int temp=array[f];
            array[f]=array[l];
            array[l]=temp;
            f++;
            l--;
        }
    }
};
