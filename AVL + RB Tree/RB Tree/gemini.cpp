#include <iostream>
using namespace std;

// Enum for readable colors
enum Color { RED, BLACK };

struct Node {
    int data;
    int size;       // <--- For Problem 1 (Command 3)
    Color color;
    Node *left, *right, *parent;

    // Constructor
    Node(int val) : data(val), size(1), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root;
    Node *TNULL; // Sentinel node (represents NULL leaves)

    // Helper to initialize TNULL
    void initializeTNULL() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->size = 0; // NULL nodes have size 0
        TNULL->left = nullptr;
        TNULL->right = nullptr;
    }

    // Helper to get size safely (handles TNULL/nullptr)
    int getSize(Node* node) {
        return (node == nullptr) ? 0 : node->size;
    }

    // Update size attribute for a node based on children
    void updateSize(Node* node) {
        if (node != TNULL) {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

    // Rotations (Crucial: Includes Size Update)
    void leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left; // <--- Identify the middle subtree

    // 1. Perform rotation
    x->right = T2;      // x takes T2 as its new right child
    
    // 2. Update T2's parent (Only if T2 is not NULL)
    if (T2 != TNULL) {
        T2->parent = x;
    }

    // 3. Link y to x's old parent
    y->parent = x->parent;
    
    if (x->parent == nullptr) {
        root = y;       // x was root, so y becomes new root
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    // 4. Finalize the link between x and y
    y->left = x;
    x->parent = y;

    // 5. Update Sizes (Order matters: x is now child of y)
    updateSize(x); // Update child first
    updateSize(y); // Update parent second
}

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        // --- SIZE UPDATE AFTER ROTATION ---
        y->size = x->size;
        updateSize(x);
    }

    // ---------------------------------------------------------
    // INSERTION FIXUP (The 3 Cases)
    // ---------------------------------------------------------
    void fixInsert(Node *k) {
        Node *u; // Uncle
        while (k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // Uncle is Left

                // CASE 1: Uncle is RED
                // Action: Recolor Parent/Uncle to Black, Grandparent to Red.
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent; // Move up to fix Grandparent
                } 
                else {
                    // CASE 2: Uncle is BLACK (Triangle / Zig-Zag)
                    // Action: Rotate Parent to make it a straight line
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    // CASE 3: Uncle is BLACK (Line / Zig-Zig)
                    // Action: Rotate Grandparent + Swap Colors
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // Uncle is Right

                // CASE 1: Uncle is RED (Mirror)
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } 
                else {
                    // CASE 2: Uncle is BLACK (Triangle) (Mirror)
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    // CASE 3: Uncle is BLACK (Line) (Mirror)
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;
    }

    // Helper for Deletion: Transplant u with v
    void rbTransplant(Node *u, Node *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // ---------------------------------------------------------
    // DELETION FIXUP (The 4 Cases)
    // "x" is the node that has the extra black weight (Double Black)
    // ---------------------------------------------------------
    void fixDelete(Node *x) {
        Node *s; // Sibling
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                
                // CASE 1: Sibling is RED
                // Action: Rotate Parent Left, Recolor. (Converts to Case 2, 3, or 4)
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right; // Update sibling pointer
                }

                // CASE 2: Sibling is BLACK, Both Nephews are BLACK
                // Action: Recolor Sibling Red. Push Double Black up to Parent.
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent; // Loop continues with Parent as new "x"
                } 
                else {
                    // CASE 3: Sibling is BLACK, Near Nephew is RED (Triangle)
                    // Action: Rotate Sibling Right. (Converts to Case 4)
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right; // Update sibling after rotation
                    }

                    // CASE 4: Sibling is BLACK, Far Nephew is RED (Line)
                    // Action: Rotate Parent Left, Swap Colors. (TERMINAL CASE)
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root; // Done. Break loop.
                }
            } else {
                // Mirror of Left cases
                s = x->parent->left;

                // CASE 1 (Mirror)
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                // CASE 2 (Mirror)
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    // CASE 3 (Mirror)
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // CASE 4 (Mirror)
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RedBlackTree() {
        initializeTNULL();
        root = TNULL;
    }

    // Command 2: Search
    Node* search(int k) {
        Node* curr = root;
        while (curr != TNULL) {
            if (curr->data == k) return curr;
            if (k < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }

    // Command 1: Initiation (Insert)
    // void insert(int key) {
    //     // Standard BST Insert with Size Update
    //     Node* node = new Node(key);
    //     node->parent = nullptr;
    //     node->data = key;
    //     node->left = TNULL;
    //     node->right = TNULL;
    //     node->color = RED; // Always insert as Red

    //     Node* y = nullptr;
    //     Node* x = root;

    //     while (x != TNULL) {
    //         y = x;
    //         x->size++; // <--- INCREMENT SIZE ON THE WAY DOWN
    //         if (node->data < x->data) x = x->left;
    //         else x = x->right;
    //     }

    //     node->parent = y;
    //     if (y == nullptr) root = node;
    //     else if (node->data < y->data) y->left = node;
    //     else y->right = node;

    //     if (node->parent == nullptr) {
    //         node->color = BLACK;
    //         return;
    //     }
    //     if (node->parent->parent == nullptr) return;

    //     fixInsert(node);
    // }

    bool insert(int key) {
    // 1. CHECK FOR DUPLICATES (Crucial Step)
    // We do this first so we don't accidentally increment 'size' 
    // for a node that we end up rejecting.
    if (search(key) != nullptr) {
        return false; // Fail: Key already exists
    }

    // 2. SETUP NEW NODE
    Node* node = new Node(key);
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED; 

    // 3. STANDARD INSERT (Safe to increment sizes now)
    Node* y = nullptr;
    Node* x = root;

    while (x != TNULL) {
        y = x;
        x->size++; // Safe to increment because we know it's unique
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // 4. LINK POINTERS
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // 5. FIXUP
    if (node->parent == nullptr) {
        node->color = BLACK;
        return true; // Success
    }
    if (node->parent->parent == nullptr) {
        return true; // Success
    }

    fixInsert(node);
    return true; // Success
}

    // Command 0: Termination (Delete)
    // void remove(int key) {
    //     Node* z = search(key);
    //     if (z == nullptr) return; // Key not found

    //     // 1. Decrement sizes on the path UP from z before we mess with links
    //     // (Wait, simpler strategy: Trace from z's parent up to root AFTER structural change)
    //     // Let's do the standard RB delete, then re-trace size.

    //     Node* y = z;
    //     Node* x;
    //     Color y_original_color = y->color;

    //     if (z->left == TNULL) {
    //         x = z->right;
    //         rbTransplant(z, z->right);
    //     } else if (z->right == TNULL) {
    //         x = z->left;
    //         rbTransplant(z, z->left);
    //     } else {
    //         // Finding successor (min of right subtree)
    //         y = z->right;
    //         while (y->left != TNULL) y = y->left;
    //         y_original_color = y->color;
    //         x = y->right;
    //         if (y->parent == z) {
    //             x->parent = y;
    //         } else {
    //             rbTransplant(y, y->right);
    //             y->right = z->right;
    //             y->right->parent = y;
    //         }
    //         rbTransplant(z, y);
    //         y->left = z->left;
    //         y->left->parent = y;
    //         y->color = z->color;
    //         y->size = z->size; // y takes z's size (roughly, needs fixup)
    //     }

    //     // --- SIZE FIXUP START ---
    //     // Walk up from the lowest point of change (x->parent) to root
    //     // and recalculate sizes.
    //     Node* fixSizeNode = x->parent;
    //     while(fixSizeNode != nullptr) {
    //         updateSize(fixSizeNode);
    //         fixSizeNode = fixSizeNode->parent;
    //     }
    //     // --- SIZE FIXUP END ---

    //     delete z;

    //     if (y_original_color == BLACK) {
    //         fixDelete(x);
    //     }
    // }


    bool remove(int key) {
        Node* z = search(key);
        if (z == TNULL || z == nullptr) return false; // Key not found

        Node* y = z; // 'y' is the node that physically leaves its current spot
        Node* x;     // 'x' is the child that replaces 'y'
        Color y_original_color = y->color;

        // --- STRUCTURAL CHANGE ---
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            // Case 3: Two children. Find Successor (y)
            y = getMinimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                // Special case: y is the direct child of z
                // We must link x to y manually because rbTransplant didn't run for y
                x->parent = y; 
            } else {
                // Standard case: y is further down
                rbTransplant(y, y->right); // y leaves its old spot
                y->right = z->right;
                y->right->parent = y;
            }

            // Move y into z's spot
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
            
            // Note: We don't strictly need to set y->size here because 
            // the loop below will reach 'y' and recalculate it correctly.
        }

        // --- SIZE FIXUP ---
        // We walk up from x->parent to the root.
        // 1. If we deleted z (Cases 1 & 2), x->parent is z's old parent. Correct.
        // 2. If we moved y (Case 3), x->parent is y's OLD parent. Correct.
        Node* fixSizeNode = x->parent;
        while (fixSizeNode != nullptr) {
            updateSize(fixSizeNode);
            fixSizeNode = fixSizeNode->parent;
        }

        // --- CLEANUP ---
        delete z; // The object 'z' is gone. 'y' (if it moved) has taken its place.

        // --- COLOR FIXUP ---
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
        
        return true; // Success
    }

    // Command 3: Find number of programs with priority < val
    int countLessThan(int val) {
        int count = 0;
        Node* curr = root;

        while (curr != TNULL) {
            if (val == curr->data) {
                // If equal, all nodes in LEFT subtree are strictly smaller
                count += getSize(curr->left);
                return count;
            }
            else if (val > curr->data) {
                // If val is greater, current node AND left subtree are smaller
                count += getSize(curr->left) + 1;
                curr = curr->right;
            }
            else {
                // If val is smaller, go left (nothing here is smaller yet)
                curr = curr->left;
            }
        }
        return count;
    }
};

int main() {
    RedBlackTree tree;
    int N;
    cin >> N; // Total commands

    for (int i = 0; i < N; i++) {
        int type, val;
        cin >> type >> val;

        if (type == 0) { // Terminate
            tree.remove(val);
        }
        else if (type == 1) { // Initiate
            // Check uniqueness if required, otherwise just insert
            if (tree.search(val) == nullptr) {
                tree.insert(val);
            }
        }
        else if (type == 2) { // Search
            Node* res = tree.search(val);
            if (res != nullptr) cout << "Found " << val << endl;
            else cout << "Not Found" << endl;
        }
        else if (type == 3) { // Count < val
            cout << tree.countLessThan(val) << endl;
        }
    }
    return 0;
}