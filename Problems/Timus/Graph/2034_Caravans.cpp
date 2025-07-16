#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
#include <queue>

using namespace std;

vector<int> bfs(vector<vector<int>>& adj, int u) {
    const int V = adj.size();
    vector<int> dist(V, INT_MAX);
    
    queue<int> que;
    que.push(u);
    dist[u] = 0;
    
    while(!que.empty()) {
        int u = que.front(); que.pop();
        
        for(auto v: adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u]+1;
                que.push(v);
            }
        }
    }
    
    return dist;
}

int dfs(vector<vector<int>>& adj, int u, int f,
        vector<int>& ds,
        vector<int>& df,
        vector<int>& dr,
        vector<int>& dp) {
    if(u==f) return dr[u]; // 1 distinct shortest-path ends here
    if(dp[u] != -1) return dp[u];
    
    int best = 0;
    for(int v: adj[u]) {
        // picking only requred edges so that we'll do path-by-path traversal
        // also making sure that vertex v lies in some shortest paths P
        if(ds[v] == ds[u]+1 &&
            ds[v] + df[v] == ds[f]) {
            // calculating the minimum distance per shortest-path that robbers can take
            int shortest_path_min_dist = dfs(adj, v, f, ds, df, dr, dp);
            
            // maximizing the minimum distance robbers have to travel
            best = max(best,
                        // cmparing how far robbers have to move from current node u
                        // to the distance v --> f and choosing minimal distance
                        min(dr[u], shortest_path_min_dist));
        }
    }
    
    // returning the best ambush distance that robbers can take in worst case
    return dp[u] = best;
}

int maxAmbushDistance(int V,
                    int S, int F, int R,
                    vector<vector<int>>& roads) {
    vector<vector<int>> adj(V+1);
    
    for(auto& e: roads) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    auto ds = bfs(adj, S); // calculating shortest distance from S --> V
    auto df = bfs(adj, F); // calculating shortest distance from F --> V
    auto dr = bfs(adj, R); // calculating shortest distance from R --> V
    
    // Now since caravan can take any shortest path so we'll pick all the
    // common vertices in all the shortest paths
    // vertex is present in some shortest paths if
    //      ds[v] + df[v] == ds[f]
    // total P shortest paths exists

	// After we got all the common vertices, robbers can teleport to any node
    // on path after caravan picks the path.

    // So robbers always picks node closest to R(Villan's Den) along that path i.e min(dr[v])
    // Caravan on other side is smart & wants to avoid getting robbed easily
    // so it chooses path P[i] where this min(dr[v]) can be maximized
    vector<int> dp(V+1, -1);
    return dfs(adj, S, F, ds, df, dr, dp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s, f, r;
    cin >> n >> m;

    vector<vector<int>> roads(m, vector<int>(2));
    for(auto& e: roads)
        cin >> e[0] >> e[1];
        
    cin >> s >> f >> r;
    
    int d = maxAmbushDistance(n, s, f, r, roads);
    cout << d << "\n";
    
    return 0;
}
