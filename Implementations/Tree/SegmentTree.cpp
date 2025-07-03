#include <bits/stdc++.h>
using namespace std;

/**
 * Header files to include
 * <iostream>   for std::ostream, std::cout
 * <vector>     for std::vector
 * <functional> for std::function
 * <algorithm>  for std::max
 *
 * 1. How to Create a Segment Tree?
 * 
 * You can create a segment tree for any associative operation (sum, min, max, etc.) by specifying:
 * - The array of elements (leaf nodes)
 * - The operation to combine nodes
 * - The identity element for the operation
 * 
 * Example: Range Sum Segment Tree (default)

    '''
        vector<int> arr = {1, 2, 3, 4, 5};
        SegmentTree<int> segTree(arr);
        // By default, this builds a segment tree for range sum queries.
    
    '''
 * - The template type <int> indicates both the array elements and the tree nodes are of type int.
 * - The default operation is sum, and the identity element is 0.
 *  
 * 
 * 2. Custom Segment Tree: Min and Max in the Same Tree
 * 
 * Suppose you want a segment tree that returns both the minimum and maximum value in a range.
 * 
 * Step 1: Define the array type
 * Since each node must store two values (min and max), use vector<int> of size 2, where:
 * - node[0] = min value in the segment
 * - node[1] = max value in the segment
 * 
 * Initialize your input array like this:

    '''
        vector<vector<int>> arr = {
            {1, 1}, {2, 2}, {3, 3}, {4, 4}
        };
        // Each leaf node contains {value, value} since min and max are same initially.
    '''
 * 
 * Step 2: Define the custom combine operation
 * The SegmentTree requires a function that combines two nodes into one — this is your operation (e.g., sum, min, max, or any custom logic).
 * The function signature must be:

    '''
        T function(const T& a, const T& b, const int level);
    '''
 * - a and b are the two child nodes to combine.
 * - level indicates the depth in the segment tree (0 = leaves, increasing upwards).
 * - It returns the combined node of type T.
 * 
 * Example: Creating a Min-Max Operation Lambda
 * If your node stores {minValue, maxValue}, represented as vector<int>, define the lambda like this:

    '''
        SegmentTree<vector<int>>::OperateFunc minMaxCombine = [](const vector<int>& a,
                                                                const vector<int>& b,
                                                                const int level) -> vector<int> {
            return { min(a[0], b[0]), max(a[1], b[1]) };
        };
    '''
 * - Here, a[0] and b[0] store minimum values.
 * - a[1] and b[1] store maximum values.
 * - The lambda returns a vector with the minimum of mins and maximum of maxes.
 * 
 * Step 3: Define the identity element
 * The identity element is what you return for an empty segment:

    '''
        vector<int> identity = {INT_MAX, INT_MIN};
    '''
 * - For minimum, identity is INT_MAX (neutral element for min)
 * - For maximum, identity is INT_MIN (neutral element for max)
 * 
 * Step 4: Create the Segment Tree
 * Now build your segment tree:

    '''
        SegmentTree<vector<int>> segTree(arr, minMaxCombine, identity);
    '''
 *
 * 
 * 3. How to Use the Segment Tree?
 * 
 * 1. Query
 * Get min and max in range [L, R] (0-based indexing):

    '''
        vector<int> result = segTree.query(L, R);
        cout << "Min: " << result[0] << ", Max: " << result[1] << "\n";
    '''
 * 
 * 2. Update
 * Update value at index idx to newVal (also a vector of size 2 in min-max case):

    '''
        segTree.update(idx, {newMinVal, newMaxVal});
    '''
 * - The index parameter in the update(index, newVal) function is 0-based.
 * - It refers to the position in the original input array — not the segment tree’s internal array.
 * - For example, update(2, newVal) updates the element at index 2 in your original array and the segment tree will adjust accordingly.
 * 
 * For example, to update the element at index 2 to value 10 (min = max = 10):

    '''
        segTree.update(2, {10, 10});
    '''
 *
 * Level-Aware Operations (Advanced Feature)
 * 
 * The combination function in this segment tree template takes an additional parameter level, which represents the depth of the current node in the segment tree.
 * This allows you to create level-dependent logic when combining nodes. 
 * 
 * Function signature:

    '''
        [](const T& a, const T& b, const int level) -> T {
            // Combine logic here
        }
    '''
 * - a, b: child nodes to combine
 * - level: distance from the leaves (0 = leaf level, increases upward)
 * 
 * Example: Alternating XOR and OR by Level
 * Suppose you're building a segment tree for a problem like Xenia and Bit Operations (Codeforces), where:
 * - The operation alternates between OR and XOR at each level of the tree.
 * - Starting from the leaves (level 0), the operations go like:
 *      - Level 0: XOR
 *      - Level 1: OR
 *      - Level 2: XOR ....
 * - Then the combination function becomes:
    '''
        SegmentTree<int>::OperateFunc bitwiseAlt = [](const int& a, const int& b, const int level) {
            return (level & 1) ? (a | b) : (a ^ b);
        };
    '''
 * - level & 1 checks if the level is odd (returns 1 for odd, 0 for even)
 * - Odd levels → a | b
 * - Even levels → a ^ b
 * 
 */

template <typename T = int>
class SegmentTree {
public:
    using OperateFunc = function<T(const T&, const T&, const int)>;
    
private:
    vector<T> segTree;
    T* arrayPtr = nullptr;
    int levels = 0;
    
    long long arraySize = 0, maxUsedIndex = 0;
    T identity;
    OperateFunc operate;
                            
    void init(T* array, long long size) {
        arrayPtr = array;
        arraySize = size;
        segTree.resize(arraySize << 2, identity);
        build(0, 0, arraySize - 1, levels);
    }
    
    void init(vector<T>& array) {
        init(array.data(), array.size());
    }

    T build(const long long i,
            const long long low, const long long high,
            const int level) {
        maxUsedIndex = max(maxUsedIndex, i);
        
        if (low==high) {
            segTree[i] = arrayPtr[low];
            return segTree[i];
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = build(left, low, mid, level-1);
        T rightVal = build(right, mid+1, high, level-1);
        
        segTree[i] = operate(leftVal, rightVal, level);
        return segTree[i];
    }
    
    void updateSegTree(const long long idx, const T newVal,
                    const long long i,
                    const long long low, const long long high,
                    const int level) {
        if (low == high) {
            segTree[i] = newVal;
            arrayPtr[idx] = newVal;
            return;
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        if (idx <= mid)
            updateSegTree(idx, newVal, left, low, mid, level-1);
        else
            updateSegTree(idx, newVal, right, mid+1, high, level-1);
        
        T leftVal = segTree[left];
        T rightVal = segTree[right];
        segTree[i] = operate(leftVal, rightVal, level);
    }
    
    T queryRange(const long long l, const long long r,
                const long long i,
                const long long low, const long long high,
                const int level) const {
        if (high < l || r < low)
            return identity;
        
        if (l <= low && high <= r)
            return segTree[i];
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = queryRange(l, r, left, low, mid, level-1);
        T rightVal = queryRange(l, r, right, mid+1, high, level-1);
        T val = operate(leftVal, rightVal, level);
        return val;
    }
    
    
public:
    
    SegmentTree(T array[], const long long N,
                OperateFunc op = [](const T& a, const T& b,
                                        const int level) { return a+b; },
                T idEle = 0) :  levels((int) ceil(log2(N))),
                                operate(op),
                                identity(idEle)
    { init(array, N); }
    
    SegmentTree(vector<T>& array,
                OperateFunc op = [](const T& a, const T& b,
                                        const int level) { return a+b; },
                T idEle = 0) :  levels((int) ceil(log2(array.size()))),
                                operate(op),
                                identity(idEle)
    { init(array); }
    
    void update(const long long i, const T newVal) {
        updateSegTree(i, newVal, 0, 0, arraySize-1, levels);
    }
    
    int getLevels() const {
        return levels;
    }
    
    long long getMaxUsedIndex() const {
        return maxUsedIndex;
    }
    
    const T& getNode(const long long i) const {
        return segTree[i];
    }
    
    T getIdentity() const {
        return identity;
    }
    
    bool isIdentity(const T& idEle) {
        return idEle == identity;
    }
    
    T query(const long long i, const long long j) const {
        return queryRange(i, j, 0, 0, arraySize-1, levels);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree<T>& st) {
        for(long long i=0; i<=st.maxUsedIndex; i++)
            os << st.segTree[i] << " ";
        return os;
    }
};
