#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> segTree;
    
    int arraySize = 0;
    int identity = 0;
    long long maxUsedIndex = 0;
    
    using OperateFunc = function<int(const int&, const int&)>;
    OperateFunc operate = [](const int& a, const int& b) { return a + b; };
    
    void init(const vector<int>& array) {
        arraySize = array.size();
        segTree.resize(arraySize << 2, identity);
        build(0, 0, arraySize - 1, array);
    }

    
    int build(const int i, const int low, const int high, const vector<int>& array) {
        maxUsedIndex = max(maxUsedIndex, (long long) i);
        
        if (low==high) {
            segTree[i] = array[low];
            return array[low];
        }
        
        int left = (i<<1) + 1;
        int right = left+1;
        int mid = low + ((high-low)>>1);
        
        int leftVal = build(left, low, mid, array);
        int rightVal = build(right, mid+1, high, array);
        
        segTree[i] = operate(leftVal, rightVal);
        return segTree[i];
    }
    
    void updateSegTree(const int idx, const int newVal, const int i, const int low, const int high) {
        if (low == high) {
            segTree[i] = newVal;
            return;
        }
        
        int left = (i<<1) + 1;
        int right = left+1;
        int mid = low + ((high-low)>>1);
        
        if (idx <= mid)
            updateSegTree(idx, newVal, left, low, mid);
        else
            updateSegTree(idx, newVal, right, mid+1, high);
        
        int leftVal = segTree[left];
        int rightVal = segTree[right];
        segTree[i] = operate(leftVal, rightVal);
    }
    
    int queryRange(const int l, const int r, const int i, const int low, const int high) {
        if (high < l || r < low)
            return identity;
        
        if (l <= low && high <= r)
            return segTree[i];
        
        int left = (i<<1) + 1;
        int right = left+1;
        int mid = low + ((high-low)>>1);
        
        int leftVal = queryRange(l, r, left, low, mid);
        int rightVal = queryRange(l, r, right, mid+1, high);
        int val = operate(leftVal, rightVal);
        return val;
    }
    
    
public:
    SegmentTree(const vector<int>& array) { init(array); }
    
    SegmentTree(const vector<int>& array,
                OperateFunc _operate,
                int idEle) : operate(_operate), identity(idEle)
    { init(array); }
    
    void update(const int i, const int newVal) {
        updateSegTree(i, newVal, 0, 0, arraySize-1);
    }
    
    int query(const int i, const int j) {
        return queryRange(i, j, 0, 0, arraySize-1);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree& st) {
        for(long long i=0; i<=st.maxUsedIndex; i++)
            os << st.segTree[i] << " ";
        return os;
    }
};

int main() {
	vector<int> array = {1,2,3,4,5};
	SegmentTree segTree(array);

    cout << segTree << "\n";
    cout << segTree.query(2,4) << "\n";
    
    return 0;
}
