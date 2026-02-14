#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;
vector<vector<pair<int,int>>>adj;

enum Color{RED,BLACK};

template<typename K,typename V>
class RBTree {
private:
    struct Node{
        K key;
        V value;
        int size;
        Color color;
        Node *left, *right, *parent;

        Node(K k,Node* dummy, V v=V()) :
            key(k), value(v), size(1), color(RED), left(dummy), right(dummy), parent(nullptr) {}
        
        //only for initializing LNULL
        Node() :
            key(K()), size(0), color(BLACK), left(this), right(this), parent(nullptr) {}

    };

    Node* root;
    Node* LNULL;

    int getSize(Node* node) // we are using LNULL so do we really need to check for node==nullptr?
    {
        return node->size;
    }

    void updateSize(Node* node)
    {
        if(node==LNULL) return;
        node->size=1+ getSize(node->left) + getSize(node->right);
    }

    void leftRotate(Node* x)
    {
        Node* y=x->right;
        Node* T2=y->left;

        x->right=T2;
        if(T2!=LNULL) T2->parent=x;
        y->parent=x->parent;

        if(x->parent==nullptr) root=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;

        y->left=x;
        x->parent=y;

        updateSize(x);
        updateSize(y);
    }

    void rightRotate(Node* x)
    {
        Node* y=x->left;
        Node* T2=y->right;

        x->left=T2;
        if(T2!=LNULL) T2->parent=x;
        y->parent=x->parent;

        if(x->parent==nullptr) root=y;
        else if(x==x->parent->left) x->parent->left=y;
        else x->parent->right=y;

        y->right=x;
        x->parent=y;

        updateSize(x);
        updateSize(y);
    }

    void fixInsert(Node* node)
    {
        Node* unc;
        while(node->parent->color==RED)
        {
            if(node->parent==node->parent->parent->right)
            {
                unc=node->parent->parent->left;

                //uncle is red so recolor parent,unlce to Black and grandpa to red
                if(unc->color==RED)
                {
                    unc->color=BLACK;
                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    node=node->parent->parent; // now try to fix grandpa
                }
                //uncle is black so multiple cases 
                else 
                {
                    //triangle
                    if(node==node->parent->left)
                    {
                        node=node->parent;
                        rightRotate(node);
                    }

                    //now all case is line
                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    leftRotate(node->parent->parent);
                }
            }
            //mirror cases
            else 
            {
                unc=node->parent->parent->right;

                if(unc->color==RED)
                {
                    unc->color=BLACK;
                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    node=node->parent->parent;
                }
                else 
                {
                    if(node==node->parent->right)
                    {
                        node=node->parent;
                        leftRotate(node);
                    }

                    node->parent->color=BLACK;
                    node->parent->parent->color=RED;
                    rightRotate(node->parent->parent);
                }
            }
            if(node==root) break;
        }
        root->color=BLACK;
    }

    void transplant(Node* u,Node* v)
    {
        if(u->parent==nullptr) root=v;
        else if(u==u->parent->left) u->parent->left=v;
        else u->parent->right=v;

        v->parent=u->parent;
    }

    //x is the double black (DB) node
    void fixDelete(Node* x)
    {
        Node* sib;
        while(x!=root && x->color==BLACK) // x red hole DB na
        {
            if(x==x->parent->left)
            {
                sib=x->parent->right;

                //sibling is red case 1
                //rotate parent to the side of DB(left) & recolor parent and sibling
                if(sib->color==RED)
                {
                    sib->color=BLACK;
                    x->parent->color=RED;
                    leftRotate(x->parent);
                    sib=x->parent->right;
                }

                //both nephews are Black and obviously sibling is black
                if(sib->left->color==BLACK && sib->right->color==BLACK)
                {
                    sib->color=RED;
                    x=x->parent;
                }
                //sibling is black but one nephew is red
                else 
                {
                    //near nephew is RED
                    if(sib->left->color==RED)
                    {
                        sib->left->color=BLACK;
                        sib->color=RED;
                        rightRotate(sib);
                        sib=x->parent->right;
                    }

                    //near nephew is BLACK
                    sib->color=x->parent->color;
                    x->parent->color=BLACK;
                    sib->right->color=BLACK;
                    leftRotate(x->parent);
                    x=root; // to break the loop cause we are done here
                }
            }
            else 
            {
                sib=x->parent->left;

                if(sib->color==RED)
                {
                    sib->color=BLACK;
                    x->parent->color=RED;
                    rightRotate(x->parent);
                    sib=x->parent->left;
                }

                if(sib->right->color==BLACK && sib->left->color==BLACK)
                {
                    sib->color=RED;
                    x=x->parent;
                }
                else 
                {
                    if(sib->right->color==RED)
                    {
                        sib->right->color=BLACK;
                        sib->color=RED;
                        leftRotate(sib);
                        sib=x->parent->left;
                    }

                    sib->color=x->parent->color;
                    x->parent->color=BLACK;
                    sib->left->color=BLACK;
                    rightRotate(x->parent);
                    x=root;
                }
            }
        }
        x->color=BLACK;
    }

    void deleteTree(Node* node)
    {
        if(node==LNULL) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }


public: 
    RBTree()
    {
        LNULL= new Node();
        root=LNULL;
    }

    ~RBTree()
    {
        deleteTree(root);
        delete LNULL;
    }

    Node* search(K key)
    {
        Node* curr=root;
        while(curr!=LNULL)
        {
            if(curr->key==key) return curr;
            if(key<curr->key) curr=curr->left;
            else curr=curr->right;
        }
        return nullptr;
    }

    bool insert(K key,V value=V())
    {
        if(search(key)!=nullptr) return false;

        Node* node= new Node(key,LNULL,value); 

        Node* p=nullptr;
        Node* curr=root;

        while(curr!=LNULL)
        {
            p=curr;
            curr->size++;
            if(key<curr->key) curr=curr->left;
            else if(key > curr->key) curr=curr->right;
        }

        node->parent=p;
        if(p==nullptr) root=node;
        else if(node->key<p->key) p->left=node;
        else p->right=node;

        //fixing
        if(node->parent==nullptr) // inserted at root
        {
            node->color=BLACK;
            return true;
        }
        //other wise call fixInsert it will handle even the parent black case lazily
        //or we can handle it here
        if(node->parent->color==BLACK) return true;

        fixInsert(node);
        return true;
    }

    Node* getSuccessor(Node* node)
    {
        node=node->right;

        while(node->left!=LNULL) node=node->left;

        return node;
    }

    bool remove(K key)
    {
        Node* z=search(key);
        if(z==nullptr) return false;

        Node* y=z;
        Node* x;
        Color y_original_color=y->color;

        if(z->left==LNULL)
        {
            x=z->right;
            transplant(z,z->right);
        }
        else if(z->right==LNULL)
        {
            x=z->left;
            transplant(z,z->left);
        }

        else 
        {
            y=getSuccessor(z);
            y_original_color=y->color;
            x=y->right;

            if(y->parent==z) x->parent=y; // this is because x can be LNULL
            else 
            {
                transplant(y,y->right);
                y->right=z->right;
                z->right->parent=y;
            }

            transplant(z,y);
            y->left=z->left;
            z->left->parent=y;
            y->color=z->color;
        }

        Node* fixSizeNode=x->parent;
        while(fixSizeNode!=nullptr)
        {
            updateSize(fixSizeNode);
            fixSizeNode=fixSizeNode->parent;
        }
        delete z;

        if(y_original_color==BLACK) fixDelete(x);

        return true;
    }

    int countLessThan(K key)
    {
        int count=0;
        Node* curr=root;

        while(curr!=LNULL)
        {
            if(curr->key==key)
            {
                count+=curr->left->size;
                return count;
            }
            else if(key>curr->key)
            {
                count+=curr->left->size+1;
                curr=curr->right;
            }
            else curr=curr->left;
        }
        return count;
    }
};

void solve()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n; 
    if(!(cin>>n)) return;
    cout<<n<<endl;
    RBTree<int,int>tree;

    for(int i=0;i<n;i++)
    {
        int e,r; cin>>e>>r;

        if(e==0)
        {
            bool success=tree.remove(r);
            cout<<e<<" "<<r<<" "<<(success ? 1: 0)<<endl;
        }
        else if(e==1)
        {
            bool success=tree.insert(r);
            cout<<e<<" "<<r<<" "<<(success ? 1: 0)<<endl;
        }
        else if(e==2)
        {
            bool success=tree.search(r);
            cout<<e<<" "<<r<<" "<<(success ? 1: 0)<<endl;

        }
        else if(e==3)
        {
            cout<<e<<" "<<r<<" "<<tree.countLessThan(r)<<endl;
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