    int kruskal(const int V, vector<vector<int>>& graph) {
        vector<int> parent(V), rank(V,0);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i

		// uses path compression to find the parent
        function<int(int)> find = [&](int u) -> int {
            if (parent[u] == u) return u;
            return parent[u] = find(parent[u]);
        };

		// uses rank to choose the new parent
        auto unite = [&](int u, int v) -> bool {
            int pu = find(u); // parent of u
            int pv = find(v); // parent of v
            
            if (pu == pv) return false;
            
            if(rank[pu] > rank[pv])
                parent[pv] = pu;
            else if (rank[pv] > rank[pu])
                parent[pu] = pv;
            else {
                parent[pu] = pv;
                rank[pv]++;
            }
            return true;
        };

		// sorting with respect to weight
		// if weights are equal then choose the lowest u
        sort(graph.begin(), graph.end(),
            [](const vector<int>& a, const vector<int>& b) -> bool {
                if (a[2]==b[2]) return a[0] < b[0];
                return a[2]<b[2];
            });
        
        int span=0;
        for(auto& e: graph) {
            int u = e[0], v = e[1], w = e[2];
            if (unite(u, v)) span += w;
        }
        
        return span;
    }
