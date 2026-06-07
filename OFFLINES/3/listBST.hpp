#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:

    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;

    // Helper: Insert
    bool inserter(Node*& node,Key k,Value v){
        if(!node){
            node=new Node(k,v);
            node_count++;
            return true;
        }
        if(k<node->key) return inserter(node->left,k,v);
        else if(k>node->key) return inserter(node->right,k,v);
        return false; 
    }

    // Helper: Find Min Node
    Node* findMinNode(Node* node) const{
        Node* cur=node;
        while(cur && cur->left){
            cur=cur->left;
        }
        return cur;
    }

    // Helper: Remove
    Node* remover(Node* node,Key k,bool& success){
        if(!node){
            success=false;
            return nullptr;
        }

        if(k<node->key){
            node->left=remover(node->left,k,success);
        } 
        else if(k>node->key){
            node->right=remover(node->right,k,success);
        } 
        else{
            success=true;

            if (!node->left){
                Node* temp=node->right;
                delete node;
                node_count--;
                return temp;
            } 
            else if(!node->right){
                Node* temp=node->left;
                delete node;
                node_count--;
                return temp;
            }

            Node* temp=findMinNode(node->right);
            node->key=temp->key;
            node->value=temp->value;

            bool dummy=true; 
            node->right=remover(node->right,temp->key,dummy);
        }
        return node;
    }

    // Helper: Find
    bool finder(Node* node,Key k) const{
        if(!node) return false;
        if(k==node->key) return true;
        return (k<node->key)?finder(node->left,k):finder(node->right,k);
    }

    // Helper: Get
    Value getter(Node* node,Key k) const{
        if(!node) throw runtime_error("Key not found");
        if(k==node->key) return node->value;
        return (k<node->key)?getter(node->left,k):getter(node->right,k);
    }

    // Helper: Clear
    void clearer(Node* node){
        if(!node) return;
        clearer(node->left);
        clearer(node->right);
        delete node;
    }

    // Helper: Print
    void printer(Node* node,char type) const{
        if(!node) return;
        if(type=='I'){          //in-order
            printer(node->left,type);
            cout<<"("<<node->key<<":"<<node->value<<") ";
            printer(node->right,type);
        } 
        else if(type=='P'){     //pre-order
            cout<<"("<<node->key<<":"<<node->value<<") ";
            printer(node->left,type);
            printer(node->right,type);
        }
        else if(type=='O'){     //post-order
            printer(node->left,type);
            printer(node->right,type);
            cout<<"("<<node->key<<":"<<node->value<<") ";
        } 
        else{                   //default(nested)
            cout<<"("<<node->key<<":"<<node->value;
            if(node->right){ 
                cout<< " ";
                if(node->left) printer(node->left,type);
                else cout<<"()";
                cout<<" ";
                printer(node->right,type);
            } 
            else if(node->left){
                cout<<" ";
                printer(node->left,type);
            }
            cout<<")";
        }
    }

public:
    ListBST() : root(nullptr), node_count(0) {}
    
    ~ListBST(){
        clear();
    }
    
    bool insert(Key key,Value value) override{
        return inserter(root,key,value);
    }
    
    bool remove(Key key) override{
        bool success=false;
        root=remover(root,key,success);
        return success;
    }
    
    bool find(Key key) const override{
        return finder(root,key);
    }

    Value get(Key key) const override{
        return getter(root,key);
    }

    void update(Key key,Value value) override{
        Node* curr=root;
        while(curr){
            if(key==curr->key){
                curr->value=value;
                return;
            }
            if(key<curr->key) curr=curr->left;
            else curr=curr->right;
        }
        throw runtime_error("Key not found");

    }

    void clear() override{
        clearer(root);
        root=nullptr;
        node_count=0;
    }
    
    size_t size() const override{
        return node_count;
    }
    
    bool empty() const override{
        return root==nullptr;
    }
    
    Key find_min() const override{
        if(!root) throw runtime_error("BST is empty");
        return findMinNode(root)->key;
    }
    
    Key find_max() const override{
        if(!root) throw runtime_error("BST is empty");
        Node* curr=root;
        while(curr->right) curr=curr->right;
        return curr->key;
    }

    void print(char traversal_type='D') const override{
        printer(root,traversal_type);
        cout<<endl;
    }
};

#endif 