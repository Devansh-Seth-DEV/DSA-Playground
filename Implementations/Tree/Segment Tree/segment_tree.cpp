#include <iostream>    // For std::cout, std::ostream
#include <vector>      // For std::vector
#include <functional>  // For std::function (custom combine operations)
#include <algorithm>   // For std::min, std::max
#include <cmath>       // For std::ceil, std::log2
#include <climits>     // For INT_MAX, INT_MIN (identity values)

using namespace std;

template <typename T = int, typename U = int>
class SegmentTree {
public:
    using CombineFunction = function<T(const T&, const T&, const int)>;
    using TransformFunction = function<T(const U&)>;
    
private:
    vector<T> vEBT;         		// van Emde Boas based segment tree takes only 2N-1 space
    CombineFunction combine;        // lambda function to combine two childs to parent
    TransformFunction transform;    // lambda function to transform U -> T
    T identity;                     // identity element useful for updating leaf-nodes
    U* arr = nullptr;       		// pointer to original array useful for updating array elements
    long long arrsz = 0;    		// size of original array
    int levels = 0;         		// total levels of tree (0-based)
                            
    void init(U* array, long long sz) {
        arr = array;    // storing the base-address of original array for updation purpose
        arrsz = sz;     // storing the size of original array for tree traversal
        
        // segment tree size 2N-1
        // using `van Emde Boas` memory layout for segment tree
        vEBT.resize((arrsz<<1)-1, identity);    // filling the segment tree with identity element
        build(0, 0, arrsz - 1, levels);         // build the optimal segment-tree
    }
    
    void init(vector<U>& array) {
        init(array.data(), array.size());
    }

    T build(const long long v,                      // v-th vertex of segment-tree
            const long long tl, const long long tr, // tree left and right range
            const int level) {
        if (tl==tr) {   // storing the leaf-nodes with U --> T transformation
            vEBT[v] = transform(arr[tl]);
            return vEBT[v];
        }
        
        
        long long tm = tl + ((tr-tl)>>1);   // mid = tl + (tr-tl)/2
        long long l = v+1;                  // left child at v + 1
        long long r = v + ((tm-tl+1)<<1);   // right child at v + 2(mid-l+1)
        
        T lval = build(l, tl, tm, level-1);
        T rval = build(r, tm+1, tr, level-1);
        
        vEBT[v] = combine(lval, rval, level);   // combining left & right child into parent v
        return vEBT[v];
    }
    
    void updatevEBT(const long long i, const U newVal,
                    const long long v,
                    const long long tl, const long long tr,
                    const int level) {
        // index bounds check, lower & upper bound
        if(i<0 || i>=arrsz) return;
        
        if (tl==tr) {
            vEBT[v] = transform(newVal);
            arr[i] = newVal;
            return;
        }
        
        long long tm = tl + ((tr-tl)>>1);
        long long l = v+1;
        long long r = v + ((tm-tl+1)<<1);
        
        if (i <= tm)
            updatevEBT(i, newVal, l, tl, tm, level-1);
        else
            updatevEBT(i, newVal, r, tm+1, tr, level-1);
        
        T lval = vEBT[l];
        T rval = vEBT[r];
        vEBT[v] = combine(lval, rval, level);
    }
    
    T queryRange(const long long L, const long long R,
                const long long v,
                const long long tl, const long long tr,
                const int level) const {
        // checking tl and tr bounds
        // if out of search bounds then return identity element
        if (L>R || tr < L || R < tl)
            return identity;
        
        // tl & tr is completely inside L & R
        if (L <= tl && tr <= R)
            return vEBT[v];
        
        // tl & tr overlaps with L & R
        long long tm = tl + ((tr-tl)>>1);
        long long l = v+1;
        long long r = v + ((tm-tl+1)<<1);
        
        T lval = queryRange(L, R, l, tl, tm, level-1);
        T rval = queryRange(L, R, r, tm+1, tr, level-1);
        T val = combine(lval, rval, level);
        return val;
    }
    
    
public:
    
    SegmentTree(U array[], const long long N,
                CombineFunction cf = [](const T& a, const T& b,
                                    const int level) -> T {
                                        return a+b;
                                    },
                T idEle = 0,
                TransformFunction tf = [](const U& a) -> T {
                                            return a;
                                        }): levels((int) ceil(log2(N))),
                                            combine(cf),
                                            identity(idEle),
                                            transform(tf)
    { init(array, N); }
    
    SegmentTree(vector<U>& array,
                CombineFunction cf = [](const T& a, const T& b,
                                    const int level) -> T {
                                        return a+b;
                                    },
                T idEle = 0,
                TransformFunction tf = [](const U& a) -> T {
                                            return a;
                                        }): levels((int) ceil(log2(array.size()))),
                                            combine(cf),
                                            identity(idEle),
                                            transform(tf)
    { init(array); }
    
    void update(const long long i, const U newVal) {
        updatevEBT(i, newVal, 0, 0, arrsz-1, levels);
    }
    
    int getLevels() const { // return total levels in segment tree
        return levels;
    }
    
    int getSize() const {   // return size of segment tree
        return (arrsz<<1)-1;
    }
    
    const T& getVertex(const long long v) const { // return the vth vertex of segment tree
        return vEBT[v];
    }
    
    T getIdentity() const { // return identity element of tree
        return identity;
    }
    
    bool isIdentity(const T& idEle,
                    function<bool(const T&,
                                const T&)> isEqual = [](const T& a,
                                                        const T& b) -> bool {
                                                        return a == b;
                                                    }) const {
        // returns true if the given identity element is correct
        return isEqual(idEle, identity);
    }
    
    T query(const long long l, const long long r) const {
        return queryRange(l, r, 0, 0, arrsz-1, levels);
    }
    
    friend ostream& operator<<(ostream& os, const SegmentTree<T, U>& t) {
        const int n = (t.arrsz<<1)-1;
        for(long long i=0; i<n; i++)
            os << t.vEBT[i] << " ";
        return os;
    }
};
