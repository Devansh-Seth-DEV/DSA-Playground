#include <bits/stdc++.h>
using namespace std;

#define N (int) 3e4+1
#define Q (int) 2e5+1
#define A (int) 1e6+1

struct QNode {
    int l, r, i;
    
    QNode() {}
    
    QNode(int l_, int r_, int i_):
        l(l_), r(r_), i(i_)
    {}
};

int arr[N], qout[Q];
QNode queries[Q];

void serve_queries(int n, int q) {
    const int BLK_SIZE = ceil(sqrt(n));
    auto cmp = [&](const QNode& a, const QNode& b) -> bool {
        int blka = a.l/BLK_SIZE, blkb = b.l/BLK_SIZE;
        if(blka == blkb) return a.r < b.r;
        return blka < blkb;
    };
    
    sort(queries, queries+q, cmp);
    
    int freq[A] = {0};
    int uniq_cnt = 0;
    int l=0, r=-1;
    
    /*
        [ Expand ] l [ shrink ] L    R [ shrink ] r [ Expand ]
    */
    
    for(int i=0; i<q; i++) {
        QNode& query = queries[i];
        
        // expanding
        while(r<(query.r-1)) {
            freq[arr[++r]]++;
            if(freq[arr[r]]==1) uniq_cnt++;
        }
        
        while(l>query.l-1) {
            freq[arr[--l]]++;
            if(freq[arr[l]]==1) uniq_cnt++;
        }
        
        // shrinking
        while(r>(query.r-1)) {
            freq[arr[r]]--;
            if(freq[arr[r--]]==0) uniq_cnt--;
        }
        
        while(l<(query.l-1)) {
            freq[arr[l]]--;
            if(freq[arr[l++]]==0) uniq_cnt--;
        }
        
        qout[query.i] = uniq_cnt;
    }
    
    
    for(int i=0; i<q; i++)
        cout << qout[i] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n;
    
    for(int i=0; i<n; i++) {
        int x; cin >> x;
        arr[i] = x;
    }
    
    cin >> q;
    
    for(int i=0; i<q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = QNode(l,r,i);
    }
    
    serve_queries(n, q);
    
    return 0;
}
