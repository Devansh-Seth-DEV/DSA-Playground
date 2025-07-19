# 🌲 Splay Tree
> A self-adjusting binary search tree with guaranteed amortized efficiency


## 📚 What is a Splay Tree?

A **Splay Tree** is a self-adjusting variant of a binary search tree. Whenever an element is accessed (via insertion, search, or deletion), it is moved to the root using a series of tree rotations:

- **Zig**: A single rotation (if node’s parent is root)
- **Zig-Zig**: Double rotation in same direction (grandparent–parent–child)
- **Zig-Zag**: Double rotation in opposite direction

This helps optimize access to frequently used elements and ensures **logarithmic amortized time** for operations.

---

## ✨ Highlights

- 🌀 **Self-adjusting BST** using splaying (zig-zig, zig-zag, zig rotations)
- 🔍 **Fast amortized operations**: insert, search, and delete in O(log n) amortized time
- 💡 **Multiple traversal methods**: inorder, preorder, postorder, level order
- 🧠 **Splaying on every access** ensures frequently accessed elements remain near root
- 🔒 **Memory-safe** with proper cleanup (no leaks)
- 🧪 Comes with a minimal **unit test file** using standard C++ assertions

<br>


## 🧩 File Structure

| File               | Description |
|--------------------|-------------|
| `splay_tree.cpp`   | Full implementation of the `SplayTree` class (single file, no headers) |
| `unit_testing.cpp` | Simple test runner with `assert()`-based unit tests |

<br>

## 🚀 How to Use

```cpp
SplayTree tree{20, 10, 30, 5, 15, 25, 35};

tree.insert(12);    // Will splay 12 to the root
tree.find(25);      // Will splay 25 to the root
tree.erase(10);     // Will splay 10, delete it, and restructure

tree.inorder();     // Output: 5 12 15 20 25 30 35
```

---

<br>

## 🧰 Supported Operations

### 🔧 Constructors

| Constructor                                | Description |
|--------------------------------------------|-------------|
| `SplayTree()`                              | Creates an empty tree |
| `SplayTree(int key)`                       | Initializes tree with a single key |
| `SplayTree(int N, int items[])`            | Initializes tree from a C-style array |
| `SplayTree(vector<int>& items)`            | Initializes tree from a `vector<int>` |
| `SplayTree(initializer_list<int> list)`    | Allows `{1, 2, 3}` syntax |
| `SplayTree(unordered_set<int>& items)`     | Initializes from a `set` (no duplicates) |

<br>

### 🌳 Core BST Operations

| Method                             | Description                                                                                    |
| ---------------------------------- | ---------------------------------------------------------------------------------------------- |
| `Node* insert(int key)`            | Inserts key and splays it to root; Returns a pointer to inserted node.                         |
| `Node* find(int key)`              | Finds key and splays it; returns node if found, else `nullptr`                                 |
| `void erase(int key)`              | Removes key if present and restructures tree                                                   |
| `bool contains(int key)`           | Returns `true` if key exists (uses `peak`)                                                     |
| `bool empty()`                     | Returns `true` if tree is empty                                                                |
| `pair<Node*, Node*> peak(int key)` | BST-style search **without splaying**; returns node (if found) and last accessed node (if not) |
| `top()`                            | Returns the root node (top of the tree). Useful for heap-like access.                          |
| `pop()`                            | Removes the root node and restructures the tree using splaying.                                |
| `popMin()`                         | Removes the minimum key node from the tree using splaying.                                     |
| `popMax()`                         | Removes the maximum key node from the tree using splaying.                                     |


<br>

### 🔁 Traversals

| Method              | Description                       |
| ------------------- | --------------------------------- |
| `void inorder()`    | Prints keys in sorted order (LNR) |
| `void preorder()`   | Prints root-left-right order      |
| `void postorder()`  | Prints left-right-root order      |
| `void levelorder()` | Prints keys level-by-level (BFS)  |

<br>

### 🧹 Utility Methods

| Method                        | Description                                |
| ----------------------------- | ------------------------------------------ |
| `void clear()`                | Deletes all nodes and resets tree to empty |
| `Node* getMin(Node* subroot)` | Returns min node in a given subtree        |
| `Node* getMax(Node* subroot)` | Returns max node in a given subtree        |
| `wipe(Node* x)`               | Deletes the specified node `x` from the tree and maintains tree structure. Requires `x` to be a valid node in the tree (e.g. from `find()`). Used internally by `pop()` and `erase()`. ⚠️ Advanced use only. |

<br>

### ⚙️ Internals You Might Use

| Member / Enum                                  | Description                                                           |
| ---------------------------------------------- | --------------------------------------------------------------------- |
| `struct Node`                                  | Tree node structure: contains `key`, `left`, `right`, `parent`        |
| `enum class RotationType`                      | Enum that categorizes which splay rotation is needed                  |
| `static RotationType getRotationType(Node* x)` | Returns type of rotation that would be performed for `x` during splay |


<br>

### 🚫 Restricted Features

| Feature                       | Reason                                                       |
| ----------------------------- | ------------------------------------------------------------ |
| Copy constructor & assignment | Deleted to prevent accidental deep copies and double deletes |
| Duplicate inserts             | Safely ignored — tree doesn't store duplicates               |
