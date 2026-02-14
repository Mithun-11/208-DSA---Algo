#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1e18;

template<typename K, typename V>
class AVLTree {
private: 
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        Node* parent; // Added Parent Pointer
        int height;

        Node(K k, V v=V()) 
            : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
    };
    
    Node* root;

    int height(Node* node) {
        if(node == nullptr) return 0;
        return node->height;
    }

    // Helper to update height based on children
    void updateHeight(Node* node) {
        if(node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    int getBalance(Node* node) {
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    // VOID Rotate: Updates structure and parent pointers directly
    void leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // 1. Link T2 to x
        x->right = T2;
        if(T2 != nullptr) T2->parent = x;

        // 2. Link y to x's parent
        y->parent = x->parent;
        if(x->parent == nullptr) root = y;
        else if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        // 3. Link x to y
        y->left = x;
        x->parent = y;

        // 4. Update heights (x first, then y)
        updateHeight(x);
        updateHeight(y);
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        Node* T2 = y->right;

        // 1. Link T2 to x
        x->left = T2;
        if(T2 != nullptr) T2->parent = x;

        // 2. Link y to x's parent
        y->parent = x->parent;
        if(x->parent == nullptr) root = y;
        else if(x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        // 3. Link x to y
        y->right = x;
        x->parent = y;

        // 4. Update heights (x first, then y)
        updateHeight(x);
        updateHeight(y);
    }

    // Rebalance a specific node if needed
    void rebalance(Node* node) {
        updateHeight(node);
        int balance = getBalance(node);

        // Left Heavy
        if(balance > 1) {
            if(getBalance(node->left) >= 0) {
                // Left Left Case
                rightRotate(node);
            } else {
                // Left Right Case
                leftRotate(node->left);
                rightRotate(node);
            }
        }
        // Right Heavy
        else if(balance < -1) {
            if(getBalance(node->right) <= 0) {
                // Right Right Case
                leftRotate(node);
            } else {
                // Right Left Case
                rightRotate(node->right);
                leftRotate(node);
            }
        }
    }

    // Helper: Iterative Transplant for Deletion
    void transplant(Node* u, Node* v) {
        if(u->parent == nullptr) root = v;
        else if(u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;

        if(v != nullptr) v->parent = u->parent;
    }

    Node* getMinimum(Node* node) {
        while(node->left != nullptr) node = node->left;
        return node;
    }

    // Recursive traversals (User requested to keep these)
    void preOrder(Node* root) {
        if(root == nullptr) return;
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    void inOrder(Node* root) {
        if(root == nullptr) return;
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }

    void postOrder(Node* root) {
        if(root == nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }

    void levelOrder(Node* root) {
        if(root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* curr = q.front();
            cout << curr->key << " ";
            q.pop();
            if(curr->left != nullptr) q.push(curr->left);
            if(curr->right != nullptr) q.push(curr->right);
        }
    }

    void destroy(Node* root) {
        if(root == nullptr) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    bool insert(K key, V value=V()) {
        Node* node = new Node(key, value);
        
        if(root == nullptr) {
            root = node;
            return true;
        }

        Node* curr = root;
        Node* p = nullptr;

        // 1. Standard BST Insert (Iterative)
        while(curr != nullptr) {
            p = curr;
            if(key < curr->key) curr = curr->left;
            else if(key > curr->key) curr = curr->right;
            else {
                delete node; // Duplicate found
                return false;
            }
        }

        node->parent = p;
        if(key < p->key) p->left = node;
        else p->right = node;

        // 2. Walk UP and Rebalance
        curr = node->parent;
        while(curr != nullptr) {
            rebalance(curr);
            curr = curr->parent; // Move up (Note: rotation might change parent structure, this handles it)
        }

        return true;
    }

    bool remove(K key) {
        Node* z = root;
        // Search for z (Iterative)
        while(z != nullptr) {
            if(key == z->key) break;
            if(key < z->key) z = z->left;
            else z = z->right;
        }

        if(z == nullptr) return false; // Key not found

        Node* y = z; 
        Node* x = nullptr;
        Node* x_parent = nullptr; // Track where to start the height update

        if(z->left == nullptr) {
            x = z->right;
            x_parent = z->parent; // Update starts at z's parent
            transplant(z, z->right);
        }
        else if(z->right == nullptr) {
            x = z->left;
            x_parent = z->parent; // Update starts at z's parent
            transplant(z, z->left);
        }
        else {
            // Case 3: Two children
            y = getMinimum(z->right);
            x = y->right;

            if(y->parent == z) {
                // Special case: y is direct child of z
                x_parent = y; 
            } else {
                x_parent = y->parent; // y was further down, start update there
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            
            // y replaces z, so y's height needs to be recalculated, 
            // but the loop below will catch it because it walks up from x_parent.
        }

        delete z;

        // --- AVL FIXUP START ---
        // Walk up from the point of structural change to the root
        Node* curr = x_parent;
        while(curr != nullptr) {
            rebalance(curr); // Rebalance checks height diff and rotates if needed
            curr = curr->parent;
        }
        // --- AVL FIXUP END ---

        return true;
    }

    void traversal(int type) {
        if(type==1) preOrder(root);
        else if(type==2) inOrder(root);
        else if(type==3) postOrder(root);
        else if(type==4) levelOrder(root);
        else cout << "Error";
        cout << endl;
    }
};