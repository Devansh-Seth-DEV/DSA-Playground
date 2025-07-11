pair<int, int> bfs(vector<vector<int>>& adj,
                const int u) {
	const int V = adj.size();
    vector<bool> visited(V, false);
    queue<int> que;

    pair<int, int> end = {u, 0}; // farthest node, distance
    que.push(u);
    visited[u] = true;

    while(!que.empty()) {
        int size = que.size(); // nodes in current level
		
        while(size--) {
            int u = que.front();
            que.pop();
            end.first = u;

            for(auto& v: adj[u]) {
                if(!visited[v]) {
                    que.push(v);
                    visited[v] = true;
                }
            }
        }

        if(!que.empty()) end.second++;
    }

    return end;
}

int diameter(vector<vector<int>>& adj) {
    // find farthest node from node 0
    auto end1 = bfs(adj, 0);

    // farthest node we got above is one end of diameter
    // find farthest node from one end of diameter to get other end of diameter
    auto end2 = bfs(adj, end1.first);
    return end2.second;
}
