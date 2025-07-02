#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> segTree;
    int items;
    int identityElement = 0;
    long long maxUsedIndex = 0;
    using OperateFunc = std::function<int(const int&, const int&)>;
    OperateFunc operate = [](const int& a, const int& b) { return a + b; };
    
    
    int build(const int i, const int low, const int high, const vector<int>& array) {
        maxUsedIndex = max(maxUsedIndex, (long long) i);
        
        if (low==high) {
            segTree[i] = array[low];
            return array[low];
        }
        
        int leftChildAt = (i<<1) + 1;
        int rightChildAt = leftChildAt+1;
        int mid = low + ((high-low)>>1);
        
        int leftChildVal = build(leftChildAt, low, mid, array);
        int rightChildVal = build(rightChildAt, mid+1, high, array);
        
        segTree[i] = operate(leftChildVal, rightChildVal);
        return segTree[i];
    }
    
    void updateSegTree(const int idx, const int newVal, const int i, const int low, const int high) {
        if (low == high) {
            segTree[i] = newVal;
            return;
        }
        
        int leftChildAt = (i<<1) + 1;
        int rightChildAt = leftChildAt+1;
        int mid = low + ((high-low)>>1);
        
        if (idx <= mid)
            updateSegTree(idx, newVal, leftChildAt, low, mid);
        else
            updateSegTree(idx, newVal, rightChildAt, mid+1, high);
        
        int leftChildVal = segTree[leftChildAt];
        int rightChildVal = segTree[rightChildAt];
        segTree[i] = operate(leftChildVal, rightChildVal);
    }
    
    int queryRange(const int start, const int end, const int i, const int low, const int high) {
        if (low > end || high < start)
            return identityElement;
        
        if (low >= start && high <= end)
            return segTree[i];
        
        int leftChildAt = (i<<1) + 1;
        int rightChildAt = leftChildAt+1;
        int mid = low + ((high-low)>>1);
        
        int leftChildVal = queryRange(start, end, leftChildAt, low, mid);
        int rightChildVal = queryRange(start, end, rightChildAt, mid+1, high);
        return operate(leftChildVal, rightChildVal);
    }
    
    
public:
    SegmentTree(const vector<int>& array) {
        items = array.size();
        segTree.resize(items<<2);
        build(0, 0, items-1, array);
    }
    
    SegmentTree(const vector<int>& array,
                OperateFunc _operate,
                int _identityElement) : operate(_operate), identityElement(_identityElement)
    {
        items = array.size();
        segTree.resize(items<<2);
        build(0, 0, items-1, array);
    }
    
    void update(const int i, const int newVal) {
        updateSegTree(i, newVal, 0, 0, items-1);
    }
    
    int query(const int i, const int j) {
        return queryRange(i, j, 0, 0, items-1);
    }
    
    void print() {
        for(long long i=0; i<maxUsedIndex; i++) {
            cout << segTree[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
	vector<int> array = {3, 1, 2, 7, 2, 1, 2, 3};
	SegmentTree segTree(array);

    segTree.print();
    
    cout << segTree.query(2, 6) << "\n";
    
    return 0;
}
