#include <bits/stdc++.h>
using namespace std;

void bfs(int u, int s,
        vector<vector<int>>& adj,
        vector<bool>& visited) {
    queue<int> que;
    que.push(u);
    visited[u] = true;
    
    int level = 0;
    
    while(!que.empty()) {
        // if strength is 0 or >= s, then
        // no need to move to next levels
        if(level >= s) break;
        
        int size = que.size();
        
        // moving to next levels till soldier' s strength
        while(size--) {
            int u = que.front();
            que.pop();
            
            for(auto& v: adj[u]) {
                if(!visited[v]) {
                    que.push(v);
                    visited[v] = true;
                }
            }
        }
        level++;
    }
}

bool isPlacementGood(int V, vector<vector<int>>& edges,
                    vector<vector<int>>& guards) {
    vector<vector<int>> adj(++V);
    
    // creating adjacency list
    for(auto& e: edges) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // visited denotes that city is protected by guard
    // visited[i] = false means city is not protected
    vector<bool> visited(V, false);
    for(auto& g: guards) {
        // if city is already protected that means
        // there exists more than 1 guard which is protecting the city
        // hence not an optimal placement so return false
        if(visited[g[0]]) return false;
        
        // if city is not protected yet then mark it protected
        // guard[0] - base city of i-th guard
        // guard[1] - strength of i-th guard
        bfs(g[0], g[1], adj, visited);
    }
    
    // additional check whether all the cities are protected or not
    for(int i=1; i<V; i++) {
        if(!visited[i]) return false;
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while(T--) {
        int N, R, M;
        cin >> N >> R >> M;
        
        vector<vector<int>> edges(R);
        for(int i=0; i<R; i++) {
            int A, B;
            cin >> A >> B;
            edges[i] = {A, B};
        }
        
        vector<vector<int>> guards(M);
        for(int i=0; i<M; i++) {
            int K, S;
            cin >> K >> S;
            guards[i] = {K, S};
        }
        
        bool res = isPlacementGood(N, edges, guards);
        cout << (res ? "Yes" : "No") << "\n";
    }
    
    return 0;
}
