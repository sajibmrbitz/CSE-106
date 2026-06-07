#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>
using namespace std;

#define MAX_CAPACITY 1000  

class MinHeap
{
private:
    int heap[MAX_CAPACITY];  // Array to store heap elements
    int size;                // Current number of elements in the heap

    /**
     * Sifts up the node at index i to maintain heap property.
     */
    void siftUp(int i)
    {
        while(i>0 && heap[(i-1)/2]>heap[i]){
            std::swap(heap[i],heap[(i-1)/2]);
            i=(i-1)/2;
        }
    }

    /**
     * Sifts down the node at index i to maintain heap property.
     */
    void siftDown(int i)
    {
        int smallest=i;
        int left=2*i+1;
        int right=2*i+2;

        if(left<size && heap[left]<heap[smallest]){
            smallest=left;
        }
            
        if(right<size && heap[right]<heap[smallest]){
            smallest=right;
        }
            
        if(smallest!=i){
            std::swap(heap[i],heap[smallest]);
            siftDown(smallest);
        }
    }

public:
    // Constructor initializes an empty heap
    MinHeap() : size(0) {}

    /**
     * Inserts a new element x into the heap.
     */
    void insert(int x)
    {
        if(size==MAX_CAPACITY) return;
        heap[size]=x;
        size++;
        siftUp(size-1);
    }

    /**
     * Returns the minimum element without removing it.
     */
    int findMin()
    {
        if(size<=0) return -1; 
        return heap[0];
    }

    /**
     * Removes and returns the minimum element from the heap.
     */
    int extractMin()
    {

        if(size<=0) return -1;
        if(size==1){
            size--;
            return heap[0];
        }

        int root=heap[0];
        heap[0]=heap[size-1];
        size--;
        siftDown(0);

        return root;
    }

    /**
     * Returns the number of elements in the heap.
     */
    int getSize()
    {
        return size;
    }

    /**
     * Checks if the heap is empty.
     * Returns true if empty, false otherwise.
     */
    bool isEmpty()
    {
        return size==0;
    }

    /**
     * Decreases the value of the element at index i to newValue.
     */
    void decreaseKey(int i, int newValue)
    {
        if(i>=size) return;
        heap[i]=newValue;
        siftUp(i);
    }

    /**
     * Deletes the element at index i.
     */
    void deleteKey(int i)
    {
        if(i>=size) return;
        decreaseKey(i,INT_MIN);
        extractMin();
    }

    /**
     * Prints the heap's content to the output file.
     * Format: "elem1 elem2 elem3 ..." (space-separated)
     */
    void printHeap(std::ofstream &outfile)
    {
        for(int i=0;i<size;i++){
            outfile<<heap[i]<<(i==(size-1)?"":" ");
        }
        outfile<<std::endl;
    }

    /**
     * Checks whether the Min Heap property is preserved.
     * Returns true if valid, false otherwise.
     */
    bool isValidMinHeap()
    {
        for(int i=0;i<=(size-2)/2;i++){
            int left=2*i+1;
            int right=2*i+2;

            if(left<size && heap[i]>heap[left]) return false;
            if(right<size && heap[i]>heap[right]) return false;
        }
        return true;

    }

    /**
     * Builds a heap from an unsorted array using bottom-up heapify.
     */
    void heapify(int arr[],int n)
    {
        size=n;
        for(int i=0;i<n;i++){
            heap[i]=arr[i];
        }

        for(int i=(size/2)-1;i>=0;i--){
            siftDown(i);
        }
    }

    /**
     * Returns all elements in sorted (ascending) order.
     * The original heap should remain UNCHANGED after this operation.
    */
    void heapSort(std::ofstream &outfile)
    {
        int tempHeap[MAX_CAPACITY];
        int tempSize=size;
        for(int i=0;i<size;i++){
            tempHeap[i]=heap[i];
        }
            

        int sorted[MAX_CAPACITY];
        int count=0;
        while(size>0){
            sorted[count++]=extractMin();
        }

        for(int i=0;i<count;i++){
            outfile<<sorted[i]<<(i==count-1?"":" ");
        }
        outfile<<std::endl;

        size=tempSize;
        for(int i=0;i<size;i++){
            heap[i]=tempHeap[i];
        }
            
    }

    /**
     * Replaces the minimum element with a new value x in a single operation.
     * Returns the old minimum value.
     */
    int replaceMin(int x)
    {
        if(size<=0) return -1;
        int oldMin=heap[0];
        heap[0]=x;
        siftDown(0);
        return oldMin;
    }
};

#endif 
