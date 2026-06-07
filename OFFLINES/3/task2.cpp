#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

struct StatData{
    int total=0, success=0, rejected=0;
};

ostream& operator<<(ostream& os,const StatData& s){
    os<<"{T:"<<s.total<<" S:"<<s.success<<" R:"<<s.rejected<<"}";
    return os;
}

void addItemToSortedArray(string items[],int &count,string newItem){
    for(int i=0;i<count;i++) 
        if(items[i]==newItem) return;

    items[count]=newItem;
    count++;

    for(int i=count-1;i>0;i--){
        if(items[i]<items[i-1]){
            string temp=items[i];
            items[i]=items[i-1];
            items[i-1]=temp;
        } 
        else break;
    }
}

int main(int argc, char **argv){
    if(argc!=2){
        cerr<<"Usage: filename\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if(!in_file){
        cerr<<"Unable to open file\n";
        return 1;
    }

    ListBST<string, int> prices;                //BST for price
    ListBST<string, StatData> stats;            //BST for statistics
    string* sortedItems=new string[200];        //array to store item IDs in sorted order
    int itemCount=0;

    int n;
    in_file>>n;
    string id;
    int bid;

    for(int i=0;i<n;i++){
        in_file>>id>>bid;
        prices.insert(id,bid);
        stats.insert(id,StatData());
        addItemToSortedArray(sortedItems,itemCount,id);
    }

    cout<<"Initial auction items:\nBST (In-order): "; prices.print('I');
    cout<<"\nAuction starts!\n\n==============================\n";

    string op;
    while(in_file>>op){
        if(op=="ADD"){
            in_file>>id>>bid;
            if(!prices.find(id)){
                prices.insert(id,bid);
                stats.insert(id,StatData());
                addItemToSortedArray(sortedItems, itemCount, id);
                cout<<"Item "<<id<<" added with starting bid "<<bid<<endl;
            }
            else{
                if(bid>prices.get(id)){
                    prices.update(id,bid);
                    cout<<"Item "<<id<<" updated with starting bid "<<bid<<endl;
                }
                else cout<<"Item "<<id<<" already exists with higher bid\n";
            }
            cout<<"BST (In-order): ";
            prices.print('I');
        } 
        else if(op=="BID"){
            in_file>>id>>bid;
            if(prices.find(id)){
                StatData s=stats.get(id);
                s.total++;
                if(bid>prices.get(id)){
                    prices.update(id,bid);
                    s.success++;
                    stats.update(id,s);
                    cout<<"Bid of "<<bid<<" on "<<id<<" accepted. Current bid: "<<bid<<endl;
                }
                else{
                    s.rejected++;
                    stats.update(id,s);
                    cout<<"Bid of "<<bid<<" on "<<id<<" rejected. Current bid: "<<prices.get(id)<<endl;
                }
            }
            else cout<<"Item "<<id<<" not found.\n";
            cout<<"BST (In-order): ";
            prices.print('I');
        }
        else if(op=="CHECK"){
            in_file>>id;
            if(prices.find(id)) cout<<"Current bid for "<<id<<": "<<prices.get(id)<<endl;
            else cout<<"Item "<<id<<" not found.\n";
            cout<<"BST (In-order): ";
            prices.print('I');
        }
        else if(op=="STATS"){
            in_file>>id;
            if(stats.find(id)){
                StatData s=stats.get(id);
                cout<<"Statistics for "<<id<<":\n"
                    <<"  Current highest bid: "<<prices.get(id)<<endl
                    <<"  Total bids placed: "<<s.total<<endl
                    <<"  Successful bids: "<<s.success<<endl
                    <<"  Rejected bids: "<<s.rejected<<endl;
            } else cout<<"Item "<<id<<" not found.\n";
        }
        else if(op=="REPORT"){
            int tBids=0,tSuc=0,tRej=0;
            for(int i=0;i<itemCount;i++){
                StatData s=stats.get(sortedItems[i]);
                tBids+=s.total;
                tSuc+=s.success;
                tRej+=s.rejected;
            }
            cout<<"Auction Report:\nTotal items: "<<itemCount
                <<"\nTotal bids placed: "<<tBids
                <<"\nTotal successful bids: "<<tSuc
                <<"\nTotal rejected bids: "<<tRej<<"\n\nItem Statistics:\n";
            
            for(int i=0;i<itemCount;i++){
                string k=sortedItems[i];
                StatData s=stats.get(k);
                cout<<"  "<<k<<": Current bid: "<<prices.get(k)
                    <<", Total bids: "<<s.total 
                    <<", Successful: "<<s.success 
                    <<", Rejected: "<<s.rejected<<endl;
            }
        }
        cout<<"==============================\n";
    }
    
    in_file.close();
    delete[] sortedItems;
    return 0;
}