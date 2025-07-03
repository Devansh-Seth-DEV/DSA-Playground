#include <bits/stdc++.h>
using namespace std;

/**
 * Header files to include
 * <iostream>   for std::ostream, std::cout
 * <vector>     for std::vector
 * <functional> for std::function
 * <algorithm>  for std::max
 */

template <typename T = int, U = vector<int>>
class SegmentTree {
public:
    using OperateFunc = function<T(const T&, const T&, const int)>;
    
private:
    vector<T> segTree;
    int levels = 0;
    
    long long arraySize = 0, maxUsedIndex = 0;
    T identity;
    OperateFunc operate;
                            
    void init(const U* array, long long size) {
        arraySize = size;
        segTree.resize(arraySize << 2, identity);
        build(0, 0, arraySize - 1, array, levels);
    }
    
    void init(const vector<U>& array) {
        init(array.data(), array.size());
    }
    
    void init(initializer_list<U> list) {
        init(list.begin(), list.size());
    }

    T build(const long long i,
            const long long low, const long long high,
            const T* array,
            const int level) {
        maxUsedIndex = max(maxUsedIndex, i);
        
        if (low==high) {
            segTree[i] = operate(array[low], identity);
            return segTree[i];
        }
        
        long long left = (i<<1) + 1;
        long long right = left+1;
        long long mid = low + ((high-low)>>1);
        
        T leftVal = build(left, low, mid, array, level-1);
        T rightVal = build(right, mid+1, high, array, level-1);
        
        segTree[i] = operate(leftVal, rightVal, level);
        return segTree[i];
    }
    
    void updateSegTree(const long long idx, const T newVal,
                    const long long i,
                    const long long low, const long long high,
                    const int level) {
        if (low == high) {
            segTree[i] = newVal;
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
                const int level) {
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
    
    SegmentTree(const U array[], const long long N,
                OperateFunc _operate = [](const T& a, const T& b,
                                        const int level) { return a+b; },
                T idEle = 0) :  levels((int) ceil(log2(N))),
                                operate(_operate),
                                identity(idEle)
    { init(array, N); }
    
    SegmentTree(const vector<U>& array,
                OperateFunc _operate = [](const T& a, const T& b,
                                        const int level) { return a+b; },
                T idEle = 0) :  levels((int) ceil(log2(array.size()))),
                                operate(_operate),
                                identity(idEle)
    { init(array); }
    
    SegmentTree(initializer_list<U> list,
                OperateFunc _operate = [](const T& a, const T& b,
                            const int level) { return a+b; },
                T idEle = 0) :  levels((int) ceil(log2(list.size()))),
                                operate(_operate),
                                identity(idEle)
    { init(list); }
    
    void update(const long long i, const T newVal) {
        updateSegTree(i, newVal, 0, 0, arraySize-1, levels);
    }
    
    int getLevels() const {
        return levels;
    }
    
    long long getMaxUsedIndex() const {
        return maxUsedIndex;
    }
    
    T& get(const long long i) {
        return segTree[i];
    }
    
    T query(const long long i, const long long j) {
        return queryRange(i, j, 0, 0, arraySize-1, levels);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree& st) {
        for(long long i=0; i<=st.maxUsedIndex; i++)
            os << st.segTree[i] << " ";
        return os;
    }
};

void printSegTree(SegmentTree<vector<int>>& st) {
    for(int i=0; i<=st.getMaxUsedIndex(); i++) {
        auto node = st.get(i);
        cout << "{" << node[0] << ", " << node[1] << "} ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    const int N = n;
	vector<int> array(N);
	for(auto& a: array) cin >> a;
	
	SegmentTree<vector<int>, int> segTree(array,
	                            [](const vector<int>& a, const vector<int>& b,
	                               const int level) -> vector<int> {
	                                   return { min(a[0], b[0]), max(a[1], b[1]) };
	                            }, {INT_MAX, INT_MIN});
    
    printSegTree(segTree);
    cout << "\n";
    
	while(q--) {
	    int type, a, b;
	    cin >> type >> a >> b;
	    
	    if (type==1) {
	        segTree.update(a, {b,b});
	    } else {
	        vector<int> res = segTree.query(a, b);
	        cout << res[0] << " " << res[1] << "\n";
	    }
	}
    
    return 0;
}
