#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;

template<typename K, typename V>
class AVLTree{
private: 
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;

        Node(K k, V v=V()) 
            : key(k),value(v),left(nullptr),right(nullptr),height(1) {}
    };
    
    Node* root;

    int height(Node* node)
    {
        if(node==nullptr) return 0;
        return node->height;
    }

    int getBalance(Node* node)
    {
        if(node==nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node* leftRotate(Node* x)
    {
        Node* y= x->right;
        Node* T2= y->left;

        y->left=x;
        x->right=T2;

        y->height = 1 + max(height(y->left),height(y->right));
        x->height = 1 + max(height(x->left),height(x->right));

        return y;
    }

    Node* rightRotate(Node* y)
    {
        Node* x= y->left;
        Node* T2= x->right;

        x->right=y;
        y->left=T2;

        y->height = 1 + max(height(y->left),height(y->right));
        x->height = 1 + max(height(x->left),height(x->right));

        return x;
    }

    Node* insertPrivate(Node* node,K key,V value,bool& success)
    {
        if(node==nullptr) 
        {
            success=true;
            return new Node(key,value);
        }

        if(key < node->key ) node->left = insertPrivate(node->left,key,value,success);

        else if(key > node->key) node->right = insertPrivate(node->right,key,value,success);

        else 
        {
            success=false;
            return node;
        }

        node->height= 1 + max(height(node->left),height(node->right));
        int balance=getBalance(node);

        if(balance>1 && key < node->left->key) return rightRotate(node);

        if(balance<-1 && key > node->right->key) return leftRotate(node);

        if(balance>1 && key > node->left->key)
        {
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }

        if(balance<-1 && key < node->right->key)
        {
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* removePrivate(Node* node,K key,bool& success)
    {
        if(node==nullptr)
        {
            success=false;
            return node;
        }

        // continue the logic from here
        // first regular BST deletion 
        // Then the 4 cases of insert
    }

    

};

void solve()
{

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int t=1;
    //cin>>t;
    for(int i=0;i<t;i++)
    {
        solve();
    }

}

//g++ -o program filename.cpp && ./program

// g++ -O2 -o program filename.cpp && ./program < input.txt > output.txt