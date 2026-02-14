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

        x->height = 1 + max(height(x->left),height(x->right));
        y->height = 1 + max(height(y->left),height(y->right));

        return y;
    }

    Node* rightRotate(Node* x)
    {
        Node* y= x->left;
        Node* T2= y->right;

        y->right=x;
        x->left=T2;

        x->height = 1 + max(height(x->left),height(x->right));
        y->height = 1 + max(height(y->left),height(y->right));

        return y;
    }

    Node* balanceAVL(Node* root)
    {
        root->height= 1 + max(height(root->left),height(root->right));
        int balance=getBalance(root);

        if(balance>1)
        {
            if(getBalance(root->left)>=0) return rightRotate(root);
            else 
            {
                root->left=leftRotate(root->left);
                return rightRotate(root);
            }
        }

        if(balance<-1)
        {
            if(getBalance(root->right)<=0) return leftRotate(root);
            else 
            {
                root->right=rightRotate(root->right);
                return leftRotate(root);
            }
        }

        return root;
    }

    Node* insertPrivate(Node* root,K key,V value,bool& success)
    {
        if(root==nullptr) 
        {
            success=true;
            return new Node(key,value);
        }

        if(key < root->key ) root->left = insertPrivate(root->left,key,value,success);

        else if(key > root->key) root->right = insertPrivate(root->right,key,value,success);

        else 
        {
            success=false;
            return root;
        }

        return balanceAVL(root);
    }

    Node* getSuccessor(Node* node)
    {
        node=node->right;

        while(node!=nullptr && node->left!=nullptr) node=node->left;

        return node;
    }

    Node* removePrivate(Node* root,K key,bool& success)
    {
        if(root==nullptr)
        {
            success=false;
            return root;
        }

        if(key < root->key) root->left=removePrivate(root->left,key,success);

        else if(key > root->key) root->right=removePrivate(root->right,key,success);

        else 
        {
            success=true;

            if(root->left==nullptr)
            {
                Node* temp=root->right;
                delete root;
                return temp;
            }

            else if(root->right==nullptr)
            {
                Node* temp=root->left;
                delete root;
                return temp;
            }

            else 
            {
                Node* succ=getSuccessor(root);
                root->key=succ->key;
                root->value=succ->value;
                bool dummy;
                root->right=removePrivate(root->right,succ->key,dummy);
            }
        }

        if(root==nullptr) return root;

        return balanceAVL(root);
    }

    void preOrder(Node* root)
    {
        if(root==nullptr) return;

        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node* root)
    {
        if(root==nullptr) return;

        inOrder(root->left);
        cout<<root->key<<" ";
        inOrder(root->right);
    }

    void postOrder(Node* root)
    {
        if(root==nullptr) return;

        postOrder(root->left);
        postOrder(root->right);
        cout<<root->key<<" ";
    }

    void levelOrder(Node* root)
    {
        if(root==nullptr) return;

        queue<Node*>q;
        q.push(root);

        while(!q.empty())
        {
            Node* curr=q.front();
            cout<<curr->key<<" ";
            q.pop();

            if(curr->left!=nullptr) q.push(curr->left);
            if(curr->right!=nullptr) q.push(curr->right);
        }
    }

    void destroy(Node* root)
    {
        if(root==nullptr) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }


public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {destroy(root); }

    bool insert(K key, V value=V())
    {
        bool success=false;
        root= insertPrivate(root,key,value,success);

        return success;
    }

    bool remove(K key)
    {
        bool success=false;
        root= removePrivate(root,key,success);

        return success;
    }

    void traversal(int type)
    {
        if(type==1) preOrder(root);
        else if(type==2) inOrder(root);
        else if(type==3) postOrder(root);
        else if(type==4) levelOrder(root);
        else 
        {
            cout<<"Error";
        }

        cout<<endl;
    }

};

void solve()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n; 
    if(!(cin>>n)) return;
    cout<<n<<endl;
    AVLTree<int,int> tree;

    for(int i=0;i<n;i++)
    {
        int e,r; cin>>e>>r;

        if(e==1)
        {
            bool success=tree.insert(r);
            cout<<"1 "<<r<<" "<<(success ? 1: 0)<<endl;
        }

        else if(e==0)
        {
            bool success=tree.remove(r);
            cout<<"0 "<<r<<" "<<(success ? 1: 0)<<endl;
        }
        else if(e==2)
        {
            tree.traversal(r);
        }

    }

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