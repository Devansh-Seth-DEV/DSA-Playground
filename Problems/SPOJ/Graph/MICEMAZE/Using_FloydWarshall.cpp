#include <bits/stdc++.h>
using namespace std;

int floydWarshall(int V, int E, int T,
                vector<vector<int>>& edges) {
	// if u and v are not connected by an edge
	// then dist[u][v] = INF a.k.a INT_MAX
    vector<vector<int>> dist(V,
                            vector<int>(V, INT_MAX));
    
    for(int u=1; u<V; u++)  // distance from u --> u is 0
        dist[u][u] = 0;
        
    for(auto& e: edges) // distance u --> v is w
        dist[ e[0] ][ e[1] ] = e[2];
    
    for(int k=1; k<V; k++) {
        for(int u=1; u<V; u++) {
            for(int v=1; v<V; v++) {
                // if no edge between (u, k) or (k, v)
                // then we'll not calculate it
                if(dist[u][k] != INT_MAX && dist[k][v] != INT_MAX) {
                    int d = dist[u][k] + dist[k][v];
                    dist[u][v] = min(dist[u][v], d);
                }
            }
        }
    }
    
    int count=0;

    // count the no. of mice reached the exit
    // in time unit T or less
    for(int u=1; u<V; u++) {
        if(dist[u][E] <= T) count++;
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
        
    int totalMiceExit = floydWarshall(N+1, E, T, edges);
    cout << totalMiceExit << "\n";
    
    return 0;
}
