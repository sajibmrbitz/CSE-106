#include <iostream>
#include <fstream>
#include <string>

#include "arrayList.h"
//#include "linkedList.h"

using namespace std;

int main() {
    ifstream file("in.txt");
    if (!file.is_open()){
        cout<<"Error: Could not open in.txt"<<endl;
        return 1;
    }
        ArrayList list;
        //LinkedList list;

    int func, param, param2;

    while(file>>func && func!=0){
        if(func==1 && file>>param){
            cout<<"Insert "<<param<<endl;
            list.insert_cur(param);
            list.print();
        } 
        else if(func==2){
            cout<<"Delete current item"<<endl;
            int ret=list.delete_cur();
            if(ret!=-1){
                list.print();
                cout<<ret<<" is deleted"<<endl;
            } else{
                cout<<"List is empty"<<endl;
            }
        } 
        else if(func==3 && file>>param){
            cout<<"Append "<<param<<endl;
            list.append(param);
            list.print();
        } 
        else if(func==4){
            cout<<"Size of the list is "<<list.size()<<endl;
        } 
        else if(func==5 && file>>param){
            cout<<"Prev "<<param<<endl;
            list.prev(param);
            list.print();
        } 
        else if(func==6 && file>>param){
            cout<<"Next "<<param<<endl;
            list.next(param);
            list.print();
        } 
        else if(func==7 && file>>param){
            if (list.is_present(param)){
                cout<<param<<" is present"<<endl;
            } else{
                cout<<param<<" is not present"<<endl;
            }
        } 
        else if(func==8){
            cout<<"Clear list"<<endl;
            list.clear();
            list.print();
        } 
        else if(func==9 && file>>param){
            cout<<"Delete "<<param<<endl;
            if(list.delete_item(param)!=-1){
                list.print();
            } else{
                cout<<param<<" not found"<<endl;
            }
        } 
        else if(func==10 && file>>param>>param2){
            cout<<"Swap index "<<param<<" and "<<param2<<endl;
            list.swap_ind(param, param2);
            list.print();
        } 
        else if(func==11 && file>>param){
            cout<<"Search "<<param<<endl;
            int ret=list.search(param);
            if(ret!=-1)
                cout<<param<<" is found at "<<ret<<endl;
            else
                cout<<param<<" is not found"<<endl;
        } 
        else if(func==12 && file>>param){
            cout<<"Find "<<param<<endl;
            int ret=list.find(param);
            if(ret!=-1)
                cout<<ret<<" is found at "<<param<<endl;
            else
                cout<<param<<" is not a valid index"<<endl;
        } 
        else if(func==13 && file>>param>>param2){
            cout<<"Update element at "<<param<<endl;
            int ret=list.update(param, param2);
            if(ret!=-1){
                list.print();
                cout<<ret<<" is updated by "<<param2<<endl;
            } else {
                cout<<param<<" is not a valid index"<<endl;
            }
        } 
        else if(func==14){
            cout<<"Trim"<<endl;
            int ret=list.trim();
            if(ret!=-1){
                list.print();
                cout<<ret<<" removed"<<endl;
            }
        } 
        else if(func==15){
            cout<<"Reverse"<<endl;
            list.reverse();
            list.print();
        }
    }

    file.close();
    return 0;
}