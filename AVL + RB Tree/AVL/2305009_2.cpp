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
        Node* parent;
        int height;

        Node(K k, V v=V()) 
            : key(k),value(v),left(nullptr),right(nullptr),parent(nullptr),height(1) {}
    };
    
    Node* root;

    int height(Node* node)
    {
        if(node==nullptr) return 0;
        return node->height;
    }

    void updateHeight(Node* node)
    {
        if(node)
        {
            node->height=1+max(height(node->left),height(node->right));
        }
    }

    int getBalance(Node* node)
    {
        if(node==nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    void leftRotate(Node* x)
    {
        Node* y=x->right;
        Node* T2=y->left;

        x->right=T2;
        if(T2!=nullptr) T2->parent=x;
        y->parent=x->parent;

        if(x->parent==nullptr) root=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;

        y->left=x;
        x->parent=y;

        updateHeight(x);
        updateHeight(y);
    }

    void rightRotate(Node* x)
    {
        Node* y=x->left;
        Node* T2=y->right;

        x->left=T2;
        if(T2!=nullptr) T2->parent=x;
        y->parent=x->parent;

        if(x->parent==nullptr) root=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;

        y->right=x;
        x->parent=y;

        updateHeight(x);
        updateHeight(y);
    }

    void rebalance(Node* node)
    {
        updateHeight(node);//first update height of current node
        int balance=getBalance(node);

        if(balance>1)
        {
            if(getBalance(node->left)>=0) rightRotate(node);
            else 
            {
                leftRotate(node->left);
                rightRotate(node);
            }
        }
        else if(balance<-1)
        {
            if(getBalance(node->right)<=0) leftRotate(node);
            else 
            {
                rightRotate(node->right);
                leftRotate(node);
            }
        }
    }

    void transplant(Node* u,Node* v)
    {
        if(u->parent==nullptr) root=v;
        else if(u==u->parent->left) u->parent->left=v;
        else u->parent->right=v;

        v->parent=u->parent;
    }

    Node* getSuccessor(Node* node)
    {
        node=node->right;

        while(node!=nullptr && node->left!=nullptr) node=node->left;

        return node;
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

    Node* search(K k)
    {
        Node* curr=root;
        while(curr!=nullptr)
        {
            if(curr->key==k) return curr;
            if(k<curr->key) curr=curr->left;
            else curr=curr->right;
        }
        return nullptr;
    }

    bool insert(K key, V value=V())
    {
        Node* node=new Node(key,value);

        Node* p=nullptr;
        Node* curr=root;

        while(curr!=nullptr)
        {
            p=curr;
            if(key<curr->key) curr=curr->left;
            else if(key > curr->key) curr=curr->right;
            else 
            {
                delete node;
                return false;
            }
        }

        node->parent=p;
        if(p==nullptr) root=node;
        else if(node->key<p->key) p->left=node;
        else p->right=node;

        curr=node->parent;
        while(curr!=nullptr)
        {
            rebalance(curr);
            curr=curr->parent;
        }

        return true;
    }

    bool remove(K key)
    {
        Node* z=search(key);
        if(z==nullptr) return false;

        Node* y=z;
        Node* x;
        Node* x_parent;

        if(z->left==nullptr)
        {
            x=z->right;
            x_parent=z->parent;
            transplant(z,z->right);
        }
        else if(z->right==nullptr)
        {
            x=z->left;
            x_parent=z->parent;
            transplant(z,z->left);
        }

        else 
        {
            y=getSuccessor(z);
            x=y->right;

            if(y->parent==z) x_parent=y;
            else 
            {
                x_parent=y->parent;
                transplant(y,y->right);
                y->right=z->right;
                z->right->parent=y;
            }

            transplant(z,y);
            y->left=z->left;
            z->left->parent=y;
        }
        delete z;

        Node* curr=x_parent;
        while(curr!=nullptr)
        {
            rebalance(curr);
            curr=curr->parent;
        }

        return true;
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