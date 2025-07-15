#include <bits/stdc++.h>
using namespace std;

int dijkstra(int V, int E, int T,
            vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> adj(++V);
    
    for(auto& e: edges) {
        // reversing all the edges
        // to find shortest path from E to all vertices
        int u = e[1], v = e[0], w = e[2];
        adj[u].push_back({v, w});
    }
    
    using P = pair<int, int>; // {w, v}

	// min-heap arranged by weight
    priority_queue<P, vector<P>, greater<P>> pq;
    vector<int> dist(V, INT_MAX); // INF distance initially
    
    pq.push({0, E}); // src is E
    dist[E] = 0; // distance from E --> E is 0
    
    while(!pq.empty()) {
        auto top = pq.top();
        int u = top.second, w = top.first;
        pq.pop();
        
        for(auto& e: adj[u]) {
            int v = e.first, wt = e.second;
            int d = w + wt;
            if (d < dist[v]) {
                dist[v] = d;
                pq.push({d, v});
            }
        }
    }
    
    int count=0;
    
    // count the no. of mice reached the exit
    // in time unit T or less
    for(int u=1; u<V; u++) {
        if (dist[u] <= T) count++;
    }
    
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, E, T, M;
    cin >> N >> E >> T >> M;
    
    vector<vector<int>> edges(M, vector<int>(3));
    
    for(auto& e: edges)
        cin >> e[0] >> e[1] >> e[2];
        
    int totalMiceExit = dijkstra(N, E, T, edges);
    cout << totalMiceExit << "\n";
    
    return 0;
}
