#include <bits/stdc++.h>
using namespace std;

template <typename T = int, typename U = int>
class SegmentTree {
public:
    using CombineFunction = function<T(const T&, const T&, const int)>;
    using TransformFunction = function<T(const U&)>;
    
private:
    vector<T> segTree;
    U* arrayPtr = nullptr;
    int levels = 0;
    
    long long arraySize = 0, maxUsedIndex = 0;
    T identity;
    CombineFunction combine;
    TransformFunction transform;
                            
    void init(U* array, long long size) {
        arrayPtr = array;
        arraySize = size;
        segTree.resize(arraySize << 2, identity);
        build(0, 0, arraySize - 1, levels);
    }
    
    void init(vector<U>& array) {
        init(array.data(), array.size());
    }

    T build(const long long i,
            const long long low, const long long high,
            const int level) {
        maxUsedIndex = max(maxUsedIndex, i);
        
        if (low==high) {
            segTree[i] = transform(arrayPtr[low]);
            return segTree[i];
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = build(left, low, mid, level-1);
        T rightVal = build(right, mid+1, high, level-1);
        
        segTree[i] = combine(leftVal, rightVal, level);
        return segTree[i];
    }
    
    void updateSegTree(const long long idx, const U newVal,
                    const long long i,
                    const long long low, const long long high,
                    const int level) {
        if (low == high) {
            segTree[i] = transform(newVal);
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
        segTree[i] = combine(leftVal, rightVal, level);
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
        T val = combine(leftVal, rightVal, level);
        return val;
    }
    
    
public:
    
    SegmentTree(U array[], const long long N,
                CombineFunction op = [](const T& a, const T& b,
                                    const int level) -> T {
                    return a+b;
                },
                T idEle = 0,
                TransformFunction tf = [](const U& a) -> T {
                    return a;
                }) :    levels((int) ceil(log2(N))),
                        combine(op),
                        identity(idEle),
                        transform(tf)
    { init(array, N); }
    
    SegmentTree(vector<U>& array,
                CombineFunction op = [](const T& a, const T& b,
                                    const int level) -> T {
                    return a+b;
                },
                T idEle = 0,
                TransformFunction tf = [](const U& a) -> T {
                    return a;
                }) :    levels((int) ceil(log2(array.size()))),
                        combine(op),
                        identity(idEle),
                        transform(tf)
    { init(array); }
    
    void update(const long long i, const U newVal) {
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
    
    bool isIdentity(const T& idEle,
                    function<bool(const T&, const T&)> isEqual = [](const T& a,
                                                                    const T& b) -> bool {
                        return a == b;
                    }) const {
        return isEqual(idEle, identity);
    }
    
    T query(const long long i, const long long j) const {
        return queryRange(i, j, 0, 0, arraySize-1, levels);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree<T,U>& st) {
        for(long long i=0; i<=st.maxUsedIndex; i++)
            os << st.segTree[i] << " ";
        return os;
    }
};
