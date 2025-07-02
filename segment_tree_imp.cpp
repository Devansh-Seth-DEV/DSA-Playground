#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    struct Node {
        int data;
        bool hasValue = false;
    };
    
    vector<Node> segTree;
    int items;
    int identityElement = 0;
    using OperateFunc = std::function<int(const int&, const int&)>;
    OperateFunc operate = [](const int& a, const int& b) { return a + b; };
    
    
    int build(const int i, const int low, const int high, const vector<int>& array) {
        if (low==high) {
            segTree[i].data = array[low];
            segTree[i].hasValue = true;
            return array[low];
        }
        
        int leftChildAt = (i<<1) + 1;
        int rightChildAt = leftChildAt+1;
        int mid = low + ((high-low)>>1);
        
        int leftChildVal = build(leftChildAt, low, mid, array);
        int rightChildVal = build(rightChildAt, mid+1, high, array);
        
        segTree[i].data = operate(leftChildVal, rightChildVal);
        segTree[i].hasValue = true;
        return segTree[i].data;
    }
    
    void updateSegTree(const int idx, const int newVal, const int i, const int low, const int high) {
        if (low == high) {
            segTree[i].data = newVal;
            return;
        }
        
        int leftChildAt = (i<<1) + 1;
        int rightChildAt = leftChildAt+1;
        int mid = low + ((high-low)>>1);
        
        if (idx <= mid)
            updateSegTree(idx, newVal, leftChildAt, low, mid);
        else
            updateSegTree(idx, newVal, rightChildAt, mid+1, high);
        
        int leftChildVal = segTree[leftChildAt].data;
        int rightChildVal = segTree[rightChildAt].data;
        segTree[i].data = operate(leftChildVal, rightChildVal);
    }
    
    int queryRange(const int start, const int end, const int i, const int low, const int high) {
        if (low > end || high < start)
            return identityElement;
        
        if (low >= start && high <= end)
            return segTree[i].data;
        
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
    
    void traverse(const bool showEmptyCell = false) {
        for(const auto& node: segTree) {
            if (node.hasValue) cout << node.data << " ";
            if (showEmptyCell) cout << "[] ";
        }
        cout << "\n";
    }
};

int main() {
	vector<int> array = {3, 1, 2, 7, 2, 1, 2, 3};
	SegmentTree segTree(array, 
			[](const int& a, const int& b) {
	    			return gcd(a, b);
			},
			0 /* identity element */ );

    segTree.traverse();
    
    cout << segTree.query(2, 6) << "\n";
    
    return 0;
}
