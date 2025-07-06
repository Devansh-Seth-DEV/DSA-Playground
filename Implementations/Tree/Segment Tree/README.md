# 📚 Segment Tree Template

## ✨ Features
- Generic for any associative operation (sum, min, max, XOR, OR, etc.)

- Level-aware operation support (e.g., alternating operations)

- Custom identity elements

- Supports composite types (like {min, max} in a node)

<br>

### 📦 Included Header Files
```cpp
#include <iostream>    // For std::cout, std::ostream
#include <vector>      // For std::vector
#include <functional>  // For std::function (custom combine operations)
#include <algorithm>   // For std::min, std::max
#include <cmath>       // For std::ceil, std::log2
#include <climits>     // For INT_MAX, INT_MIN (identity values)
```

<br>

## 🚀 How to Create a Segment Tree
You can create a segment tree for any associative operation (like sum, min, max) by specifying:

- **The array of elements**: This is your original data — could be integers, structs, or any other type.

- **The operation to combine nodes**: A binary operation like sum, min, max, etc. It should be associative and accept an extra parameter: the level of the node in the tree.

- **The identity element for the operation**: The neutral element for your combine function (e.g., 0 for sum, INT_MAX for min, etc.)

- **A function to transform each input element into a tree node**: Used when your node type `T` is different from input type `U`. For example, transforming an `int` into a `{min, max}` pair: {a, a}.

### ➕ Example: Range Sum Segment Tree
```cpp
vector<int> arr = {1, 2, 3, 4, 5};
SegmentTree<int, int> segTree(arr);  // Builds a segment tree for range sum queries by default
```

- Template type T=`int` and U=`int` indicates the type of nodes and elements in array respectively.

- Default operation is `sum`, and identity element is `0`.

<br>

## 🛠 Custom Segment Tree: Min and Max in the Same Tree
### 🧱 Step 1: Define the array type
```cpp
vector<int> arr = {11, 3, 7, 5, 9, 1};
```

<br>

### ⚙️ Step 2: Define the custom combine operation
```cpp
SegmentTree<vector<int>, int>::CombineFunction minMaxCombine = [](const vector<int>& a,
                                                                 const vector<int>& b,
                                                                 const int level) -> vector<int> {
    return { min(a[0], b[0]), max(a[1], b[1]) };
};
```
- `a[0]`, `b[0]`: min values

- `a[1]`, `b[1]`: max values

<br>

### 🧩 Step 3: Define the identity element
```cpp
vector<int> identity = {INT_MAX, INT_MIN};
```

- Neutral for `min` → `INT_MAX`

- Neutral for `max` → `INT_MIN`

<br>

### 🔁 Step 4: Define the transform function
```cpp
SegmentTree<vector<int>, int>::TransformFunction minMaxTransform = [](const int& val) -> vector<int> {
    return {val, val};
};
```

- Converts raw integer into a `{min, max}` pair

- This function is applied at the leaf level when building the segment tree

<br>

### 🏗 Step 5: Create the Segment Tree
```cpp
SegmentTree<vector<int>, int> segTree(arr, minMaxCombine, identity, minMaxTransform);
```

- `T = vector<int>` → This is the node type stored in the segment tree.
In this case, each node stores two values: {min, max} for a range.

- `U = int` → This is the input type in the original array (arr).
Each element in the input is a plain integer, like 1, 2, 3, etc

<br>

## 🔍 How to Use the Segment Tree?
### ✅ Query
Get min and max in range [L, R] (0-based):
```cpp
vector<int> result = segTree.query(L, R);
cout << "Min: " << result[0] << ", Max: " << result[1] << "\n";
```
### ➕ Example: Query in range [L = 0, R = 2]
```cpp
vector<int> result = segTree.query(0, 2);
cout << "Min: " << result[0] << ", Max: " << result[1] << "\n";
```
#### Output
```bash
Min: 3, Max: 11
```

<br>

### 🔄 Update
Update value at index idx to new value (must be of same type as `U`):
```cpp
segTree.update(idx, newVal);
```
### ➕ Example: Update index 3 to 17
```cpp
segTree.update(3, 17);
```
#### Output 
```bash
arr = {11, 3, 7, 5, 9, 1} // old array
arr = {11, 3, 7, 17, 9, 1} // updated array
```

<br>

## 🧠 Level-Aware Operations (Advanced Feature)
You can build logic that depends on the depth (level) in the segment tree.

### 📌 Function Signature
```cpp
[](const T& a, const T& b, const int level) -> T {
    // Combine logic here
}
```

- `a`, `b`: child nodes

- `level`: depth from leaves (0 = leaf level)


### ➕ Example: Alternating XOR and OR by Level
Used in problems like Xenia and Bit Operations:
```cpp
SegmentTree<int>::CombineFunction bitwiseAlt = [](const int& a,
                                            const int& b,
                                            const int level) {
    return (level & 1) ? (a | b) : (a ^ b);
};
```

- Even levels → XOR

- Odd levels → OR
