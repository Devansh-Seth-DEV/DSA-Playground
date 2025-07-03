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

- The array of elements (leaf nodes)

- The operation to combine nodes

- The identity element for the operation

### ➕ Example: Range Sum Segment Tree
```cpp
vector<int> arr = {1, 2, 3, 4, 5};
SegmentTree<int> segTree(arr);  // Builds a segment tree for range sum queries by default
```

- Template type **\<int\>** indicates the type of both array and nodes.

- Default operation is sum, and identity element is 0.

<br>

## 🛠 Custom Segment Tree: Min and Max in the Same Tree
### 🧱 Step 1: Define the array type
Each node stores two values: {min, max}
```cpp
vector<vector<int>> arr = {
    {1, 1}, {2, 2}, {3, 3}, {4, 4}
};
// Each leaf is initialized as {value, value}
```

<br>

### ⚙️ Step 2: Define the custom combine operation
```cpp
SegmentTree<vector<int>>::OperateFunc minMaxCombine = [](const vector<int>& a,
                                                         const vector<int>& b,
                                                         const int level) -> vector<int> {
    return { min(a[0], b[0]), max(a[1], b[1]) };
};
```
- a[0], b[0]: min values

- a[1], b[1]: max values

<br>

### 🧩 Step 3: Define the identity element
```cpp
vector<int> identity = {INT_MAX, INT_MIN};
```

- Neutral for min → INT_MAX

- Neutral for max → INT_MIN

<br>

### 🏗 Step 4: Create the Segment Tree
```cpp
SegmentTree<vector<int>> segTree(arr, minMaxCombine, identity);
```

<br>

## 🔍 How to Use the Segment Tree?
### ✅ Query
Get min and max in range [L, R] (0-based):
```cpp
vector<int> result = segTree.query(L, R);
cout << "Min: " << result[0] << ", Max: " << result[1] << "\n";
```

<br>

### 🔄 Update
Update value at index idx to new value (must be of same type):
```cpp
segTree.update(idx, {newMinVal, newMaxVal});
```
Example: Update index 2 to 10:
```cpp
segTree.update(2, {10, 10});
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

- a, b: child nodes

- level: depth from leaves (0 = leaf level)


### ➕ Example: Alternating XOR and OR by Level
Used in problems like Xenia and Bit Operations:
```cpp
SegmentTree<int>::OperateFunc bitwiseAlt = [](const int& a,
                                            const int& b,
                                            const int level) {
    return (level & 1) ? (a | b) : (a ^ b);
};
```

- Even levels → XOR

- Odd levels → OR
