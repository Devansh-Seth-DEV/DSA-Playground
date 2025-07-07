#include <bits/stdc++.h>
using namespace std;

struct SegNode {
    int sum;
    int pref, suff;
    int maxsum;
  
    SegNode(): sum(0), pref(0), suff(0), maxsum(0)
    {}
    
    SegNode(int s): sum(s),
                    pref(max(0, s)), suff(max(0,s)),
                    maxsum(max(0,s))
    {}
};

SegNode merge_segnode(const SegNode& l, const SegNode& r) {
    SegNode mrg;
    mrg.sum     = r.sum + l.sum;
	// max prefix sum [l, r]
    mrg.pref    = max(l.pref, l.sum + r.pref);
	// max suffix sum [l, r]
    mrg.suff    = max(r.suff, r.sum + l.suff);
	// max sum of segment [l, r]
    mrg.maxsum  = max(max(l.maxsum, r.maxsum),
                    l.suff + r.pref);
    return mrg;
}

void build_segtree(vector<SegNode>& t, const vector<int>& arr,
            const int v,
            const int tl, const int tr) {
    if(tl == tr) {
        t[v] = SegNode(arr[tl]);
    } else {
        int tm = tl + ((tr-tl)>>1);
        int vl = v+1;
        int vr = v + ((tm-tl+1)<<1);
        
        build_segtree(t, arr, vl, tl, tm);
        build_segtree(t, arr, vr, tm+1, tr);
        
        t[v] = merge_segnode(t[vl], t[vr]);
    }
}


vector<SegNode> get_segtree(const vector<int>& arr) {
    const int N = (arr.size()<<1)-1;
    vector<SegNode> t(N);
    build_segtree(t, arr, 0, 0, N-1);
    return t;
}

SegNode maxsum_queryRec(vector<SegNode>& t,
                        const int v,
                        const int tl, const int tr,
                        const int l, const int r) {
    // out-of-range check
    if (l > r || tr < l || r < tl)
        return SegNode();
        
    //completely inside range
    if (l <= tl && tr <= r)
        return t[v];
    
    //overlapping range (partially inside)
    int tm  = tl + ((tr-tl)>>1);
    int vl = v+1;
    int vr = v + ((tm-tl+1)<<1);
    
    auto ql = maxsum_queryRec(t, vl, tl, tm, l, r);
    auto qr = maxsum_queryRec(t, vr, tm+1, tr, l, r);
    return merge_segnode(ql, qr);
}

int maxsum_query(vector<SegNode>& t, int l, int r) {
    auto q = maxsum_queryRec(t, 0, 0, t.size()-1, l, r);
    return q.maxsum;
}

void upd_queryRec(vector<SegNode>& t,
                const int v,
                const int tl, const int tr,
                const int i, const int val) {
    if (tl==tr) {
        t[v] = SegNode(val);
        return;
    }
    
    int tm  = tl + ((tr-tl)>>1);
    int vl = v+1;
    int vr = v + ((tm-tl+1)<<1);
    
    if (i<=tm)
        upd_queryRec(t, vl, tl, tm, i, val);
    else
        upd_queryRec(t, vr, tm+1, tr, i, val);
    
    t[v] = merge_segnode(t[vl], t[vr]);
}

void upd_query(vector<SegNode>& t, vector<int>& arr,
            const int i, const int val) {
    if(i<0 || i>=arr.size()) return;
    upd_queryRec(t, 0, 0, t.size()-1, i, val);
    arr[i] = val;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> arr(n);
    for(auto& a: arr) cin >> a;

	// uses "van Emde Boas-style layout" for building segment tree
	// it builds segment tree in exactly 2N-1 space
    auto t = get_segtree(arr); // O(N)

	// Time Complexity: O(Q x logN)
    while(q--) {
        int op;
        cin >> op;
        
        if (op==1) {
            int l, r;
            cin >> l >> r;
            int mxsum = maxsum_query(t, l, r); // O(logN)
            cout << mxsum << "\n";
        } else {
            int i, val;
            cin >> i >> val;
            upd_query(t, arr, i, val); // O(logN)
        }
    }
	
    return 0;
}
