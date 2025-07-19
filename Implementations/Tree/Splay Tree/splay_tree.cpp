#include <iostream>
#include <vector>
#include <functional>
#include <unordered_set>
#include <queue>

using namespace std;

class SplayTree {
public:
    SplayTree() {}
    
    SplayTree(int key): root(new Node(key))
    {}
    
    SplayTree(int N, int items[]) {
        for(int i=0; i<N; i++)
            insert(items[i]);
    }
    
    SplayTree(vector<int>& items) {
        for(int x: items)
            insert(x);
    }
    
    SplayTree(initializer_list<int> list) {
        for(int x: list)
            insert(x);
    }
    
    SplayTree(unordered_set<int>& setItems) {
        for(int s: setItems)
            insert(s);
    }
    
    ~SplayTree() {
        clear(); // avoid memory leaks
    }
    
    // diable copy constructor & copy assignment
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    
    struct Node {
        int key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        
        Node(int k): key(k)
        {}
    };

    enum class RotationType {
        NO_ROTATION,
        ZIG_LEFT, ZIG_RIGHT,    //zig rotations
        ZIG_ZIG_LEFT, ZIG_ZIG_RIGHT,    // zig-zig rotations
        ZIG_ZAG_LEFT_RIGHT, ZIG_ZAG_RIGHT_LEFT, // zig-zag rotations
    };
    
    static RotationType getRotationType(Node* x) {
        if(!x || !x->parent) // if x is null or x is root then no rotation
            return RotationType::NO_ROTATION;
        
        Node* p = x->parent;
        Node* g = p->parent;
        
        if(!g) { // zig operation
            if(p->left == x)
                // when x is left child of its parent p
                // so x will do a single right rotation around p
                return RotationType::ZIG_RIGHT;
            // when x is right child of its parent p
            // so x will do a single left rotation around p
            return RotationType::ZIG_LEFT;
        }
        
        if(g->left == p && p->left == x)
            // zig-zig (left-left) operation
            // when x is left child of p, and p is also the left child of g
            return RotationType::ZIG_ZIG_LEFT;
        
        if(g->right == p && p->right == x)
            // zig-zig (right-right) operation
            // when x is right child of p, and p is also the right child of g
            return RotationType::ZIG_ZIG_RIGHT;
            
        if(g->left == p && p->right==x)
            // zig-zag (left-right) operation
            // when x is right child of p, and p is the left child of g
            return RotationType::ZIG_ZAG_LEFT_RIGHT;
            
        // zig-zag (right-left) operation
        // when x is left child of p, and p is the right child of g
        return RotationType::ZIG_ZAG_RIGHT_LEFT;
    }
    
    Node* insert(int key) {
        Node* x = bstInsert(key);
        splay(x);
        return x;
    }
    
    bool empty() {
        return root==nullptr;
    }
    
    bool contains(int key) {
        pair<Node*, Node*> p = peak(key);
        return p.first != nullptr;
    }
    
    pair<Node*, Node*> peak(int key) {
        Node* it = root;
        Node* p = nullptr;
        
        // traverse like normal bst search
        while(it) {
            p = it;
            
            if(key == it->key) { // key found
                // return pair of key node & last accessed node
                return {it, nullptr};
            }
            
            if(key < it->key)
                it = it->left;
            else it = it->right;
        }
        
        // key not found
        // return pair of key node & last accessed node
        return {nullptr, p};
    }
    
    Node* find(int key) {
        // Step-1: Traverse like normal BST search
        pair<Node*, Node*> p = peak(key);
        Node* x = p.first;
        Node* last = p.second;
        
        if(x) {  // Step-2: If key is found, splay it to root
            splay(x);
            return x;
        }
        
        // Step-3: if key not found, splay the last accessed node to root
        //          i.e closes to where key would have been
        if (last) splay(last);
        return nullptr;
    }
    
    void erase(int key) {
        // Step-1: Find the key and splay it to root
        Node* x = find(key);
        if (!x) return; // key not found
        
        // Step-2: Since key is found, erase the key
        //          also disconnect it from its childrens
        Node* lchild = x->left;
        Node* rchild = x->right;
        
        // disconnect x from its childrens
        if (lchild) lchild->parent = nullptr;
        if (rchild) rchild->parent = nullptr;
        
        delete x; // saftey remove key after disconnecting childs
        x = nullptr; // avoid dangling pointer issue, good practice
        
        // Step-3: Join the remaining subtree by following cases
        // case1: remaining left subtree is not null in that case
        //      1. splay the max node in the left subtree to top
        //      2. attach remaining right subtree to the right of this max node(new root)
        // case2: no remaining left subtree, in this case just set root to right subtree
        if (lchild) {
            Node* maxNode = getMax(lchild); // get max node from left subtree
            splay(maxNode); // splay the max node to top of the tree
            
            // attach right subtree to root
            root->right = rchild;
            if(rchild) rchild->parent = root;
        } else root = rchild; // no left subtree so making right child as new root
    }
    
    void clear() {
        function<void(Node*)> clearRec = [&](Node* x) {
            if (!x) return;
            clearRec(x->left);  // clear left subtree
            clearRec(x->right); // clear right subtree
            delete x;   // clear the leaf node or root
        };
        
        clearRec(root);
        root = nullptr; // reset the tree root
    }
    
    Node* getMax(Node* subtRoot) {
        Node* it = subtRoot;
        if(!it) return nullptr;
        
        while(it->right)
            it = it->right;
        return it;
    }
    
    Node* getMin(Node* subtRoot) {
        Node* it = subtRoot;
        if(!it) return nullptr;
        
        while(it->left)
            it = it->left;
        return it;
    }
    
    void inorder() {
        function<void(Node*)> traverse = [&](Node* x) {
            if(!x) return;
            
            traverse(x->left);
            cout << x->key << " ";
            traverse(x->right);
        };
        
        if(root) {
            traverse(root);
            cout << "\n";
        }
    }
    
    void preorder() {
        function<void(Node*)> traverse = [&](Node* x) {
            if(!x) return;
            
            cout << x->key << " ";
            traverse(x->left);
            traverse(x->right);
        };
        
        if(root) {
            traverse(root);
            cout << "\n";
        }
    }
    
    void postorder() {
        function<void(Node*)> traverse = [&](Node* x) {
            if(!x) return;
            
            traverse(x->left);
            traverse(x->right);
            cout << x->key << " ";
        };
        
        if(root) {
            traverse(root);
            cout << "\n";
        }
    }
    
    void levelorder() {
        queue<Node*> que;
        if(root)
            que.push(root);
        
        while(!que.empty()) {
            size_t size = que.size();
            while(size--) {
                Node* x = que.front(); que.pop();
                
                cout << x->key << " ";
                if(x->left)
                    que.push(x->left);
                if (x->right)
                    que.push(x->right);
            }
        }
        if(root) cout << "\n";
    }
    
private:
    Node* root = nullptr;
    
    void rotateRight(Node* p) {
        if (!p) return; // saftey
        
        /*
            zig when x is the left child of p (single right rotation)
            Here A, B, C denotes subtree of x and p respectively
            
                  p               x
                /   \   --->    /   \
               x     C         A     p
             /   \                 /   \
            A     B               B     C
        
        */
        
        Node* x = p->left; // will apply right rotation on left child of p
        Node* g = p->parent; // grandparent of x (if exists)
        if(!x) return; // no left child to rotate
        Node* subtB = x->right; // subtree B
    
        // connecting subtree B as left child of p
        p->left = subtB;
        // If subtree(B) exists, set its parent to p (as B becomes p's left child)
        if(subtB) subtB->parent = p;
        
        // connecting grandparent(if exists) to x
        // this detach p from its parent g (grandparent of x)
        if(g) {
            //check which child of 'g' should be made 'x', left or right
            if(g->left == p)
                g->left = x;
            else g->right = x;
        }
        
        x->parent = g; // g is no more grandparent of x, its parent now
        x->right = p; // p is right child of x now
        p->parent = x; // x is now parent of p
    }
    
    void rotateLeft(Node* p) {
        if (!p) return; // saftey
        
        /*
            zig when x is the right child of p (single left rotation)
            Here A, B, C denotes subtree of x and p respectively
            
                  p                     x  
                /   \                 /   \
               C     x      --->     p     A
                   /   \           /   \
                  B     A         C     B
        
        */
        
        Node* x = p->right; // will apply left rotation on right child of p
        Node* g = p->parent; // grandparent of x (if exists)
        if(!x) return; // no right child to rotate
        Node* subtB = x->left; // subtree B
    
        // connecting subtree B as right child of p
        p->right = subtB;
        // If subtree(B) exists, set its parent to p (as B becomes p's right child)
        if(subtB) subtB->parent = p;
        
        // connecting grandparent(if exists) to x
        // this detach p from its parent g (grandparent of x)
        if(g) {
            //check which child of 'g' should be made 'x', left or right
            if(g->left == p)
                g->left = x;
            else g->right = x;
        }
        
        x->parent = g; // g is no more grandparent of x, its parent now
        x->left = p; // p is left child of x now
        p->parent = x; // x is now parent of p
    }
    
    void splay(Node* x) {
        while(x && x->parent) { // while x is not root, continue rotating it
            RotationType r = getRotationType(x);
            
            switch(r) {
                case RotationType::ZIG_RIGHT:   // right rotate parent p along x
                    rotateRight(x->parent); break;
                
                case RotationType::ZIG_LEFT:    // left rotate parent p along x
                    rotateLeft(x->parent); break;
                
                case RotationType::ZIG_ZIG_LEFT:
                    rotateRight(x->parent->parent); // right rotate g first then
                    rotateRight(x->parent); // right rotate p
                    break;
                
                case RotationType::ZIG_ZIG_RIGHT:
                    rotateLeft(x->parent->parent); // left rotate g first then
                    rotateLeft(x->parent); // left rorate p
                    break;
                    
                case RotationType::ZIG_ZAG_LEFT_RIGHT:
                    rotateLeft(x->parent); // left rotate p first then
                    rotateRight(x->parent->parent); // right rotate g
                    break;
                    
                case RotationType::ZIG_ZAG_RIGHT_LEFT:
                    rotateRight(x->parent); // right rotate p first then
                    rotateLeft(x->parent->parent); // left rotate g
                    break;
                    
                default: break; // no rotation
            }
        }
        
        root = x;  // updating root to x as x is the new root of tree now
    }
    
    Node* bstInsert(int key) {
        Node* x = new Node(key);
        Node* p = nullptr;
        Node* it = root;
        
        while(it) {
            p = it; // update potential parent
            if (key == it->key) {
                delete x; // avoid memory leak
                return it; // key already exists, no insertion
            }
                
            if(key < it->key) // if key is smaller then seach its attaching position in left
                it = it->left;
            else it = it->right; // if key is larget then search its attaching position in right
        }
        
        x->parent = p; // updating the parent of x
        
        if(!p) // tree was empty
            root = x;
        else if (key < p->key)
            // if key of x is less than its parent then attach it to its parent's left
            p->left = x;
        // if key of x is greater than its parent then attach it to its parent's right
        else p->right = x;
        
        return x;
    }
};
