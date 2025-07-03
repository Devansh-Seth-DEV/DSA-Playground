/**
 * Header files to include
 * <iostream>   for std::ostream, std::cout
 * <vector>     for std::vector
 * <functional> for std::function
 * <algorithm>  for std::max
 */

template <typename T = int, typename U = int>
class SegmentTree {
private:
    vector<T> segTree;
    
    long long arraySize = 0, maxUsedIndex = 0;
    T identity = 0;
    
    using OperateFunc = function<T(const T&, const T&)>;
    OperateFunc operate = [](const T& a, const T& b) { return a + b; };
    
    void init(const vector<U>& array) {
        arraySize = array.size();
        segTree.resize(arraySize << 2, identity);
        build(0, 0, arraySize - 1, array);
    }

    
    T build(const long long i, const long long low, const long long high, const vector<U>& array) {
        maxUsedIndex = max(maxUsedIndex, i);
        
        if (low==high) {
            segTree[i] = (T) array[low];
            return segTree[i];
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = build(left, low, mid, array);
        T rightVal = build(right, mid+1, high, array);
        
        segTree[i] = operate(leftVal, rightVal);
        return segTree[i];
    }
    
    void updateSegTree(const long long idx, const T newVal, const long long i, const long long low, const long long high) {
        if (low == high) {
            segTree[i] = newVal;
            return;
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        if (idx <= mid)
            updateSegTree(idx, newVal, left, low, mid);
        else
            updateSegTree(idx, newVal, right, mid+1, high);
        
        T leftVal = segTree[left];
        T rightVal = segTree[right];
        segTree[i] = operate(leftVal, rightVal);
    }
    
    T queryRange(const long long l, const long long r, const long long i, const long long low, const long long high) {
        if (high < l || r < low)
            return identity;
        
        if (l <= low && high <= r)
            return segTree[i];
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = queryRange(l, r, left, low, mid);
        T rightVal = queryRange(l, r, right, mid+1, high);
        T val = operate(leftVal, rightVal);
        return val;
    }
    
    
public:
    SegmentTree(const vector<U>& array) { init(array); }
    
    SegmentTree(const vector<U>& array,
                OperateFunc _operate,
                T idEle) : operate(_operate), identity(idEle)
    { init(array); }
    
    void update(const long long i, const T newVal) {
        updateSegTree(i, newVal, 0, 0, arraySize-1);
    }
    
    T query(const long long i, const long long j) {
        return queryRange(i, j, 0, 0, arraySize-1);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree& st) {
        for(long long i=0; i<=st.maxUsedIndex; i++)
            os << st.segTree[i] << " ";
        return os;
    }
};
