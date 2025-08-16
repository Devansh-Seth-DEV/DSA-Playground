#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        n m s
        u   v   w
         1   1   1
        u   v   w
         2   2   2
        
        .
        .
        .
        u   v   w
         m   m   m
*/

class Solution {
    /*
        Let G = (V, E, w)
        where:
            V ⊆ ℤ+ U {0}
            E ⊆ V x V
            w: E -> ℤ (weight function - assign integer weight to every edge)
    */
    int V; // total number of vertices in graph G
    
    /*
        α    - Adjacency pair
         u,v
        For each vertex u, the adjacency pair denotes tuple consisting of 
        vertex v and weight of edge from u to v
        
        defined as:
            α   := (v, w(u, v)) where v ϵ V, (u, v) ϵ E 
             u,v
    */
    using alpha_uv = pair<int, int>;

    /*   +
        Γ (u) - Directed Neighbour function (+ indicates out-degree of u i.e u->v)
         G
        tells the neighbours of u (directly connected)
        
        defined as:
             +
            Γ (u) := { α    | v ϵ V, (u, v) ϵ E }
             G          u,v
    */
    vector<vector<alpha_uv>> GammaPlus_G;

    /*
        Reach (u) - Reachability function
             G
        set of all vertices that are reachable from u in other words
        set of all vertices such that there exists a path from u to v
            
        defined as:
            Reach (u) := { v ϵ V | ∃ a path length >= 0 from u to v }
                 G
                     +
        In terms of Γ (u):
                     G
                                       
            Reach (u) := {u} U U    +  ( Reach (x) )
                 G             x ϵ Γ          G
                                    G
                                                +
            if x is direct neighbour of u (x ϵ Γ (u)) then 
                                                G 
            anything reachable from x is also reachable from u
            
            So:
               U    +  ( Reach (x) ) means:
               x ϵ Γ          G
                    G
                                     +
                    - For each x in Γ (u) take the set Reach (x)
                                     G                      G
                    - Union all these sets together into one big set.
    */
    unordered_set<int> Reach_G(int u) {
        unordered_set<int> reach;
        reach.insert(u);
        
        vector<bool> visited(V, false);
        queue<int> que;
        que.push(u);
        visited[u] = true;
        
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            
            for(auto& alpha_xv: GammaPlus_G[x]) {
                int v = alpha_xv.first;
                if(visited[v]) continue;
                
                visited[v] = true;
                reach.insert(v);
                que.push(v);
            }
        }
        
        return reach;
    }
    
    /*   max
        Π    - Maximum Path Function
         u->v
         
        The length of the maximum-weight path from u to v
        
        defined as:
             max
            Π     := { max {(p, l(p)) | p is a path from u to v},  v ϵ Reach (u)
             u->v    {                                                      G
                     { -∞,                                         otherwise
        where:
            l(p) = ∑    w(e)
                   e ϵ p
    */
    vector<alpha_uv> PImax_uv(int u, int v) {
        vector<alpha_uv> p(V, {-INT_MIN, -INT_MIN}); // path vector
        p[u] = {0, u}; // path from u -> u has minimum weight 0

        queue<alpha_uv> que;
        que.push({u, 0});
        
        while(!que.empty()) {
            auto f = que.front();
            int x = f.first;
            int wt_ux = f.second; // weight from u->x
            
            que.pop();
            for(auto& alpha_xy: GammaPlus_G[x]) {
                int y = alpha_xy.first;
                int wt_xy = alpha_xy.second; // weight from x->y
                 
                int wt_uxy = wt_ux + wt_xy; // sum weight of u->x & x->y i.e u->y
                    
                if(p[y].second == -INT_MIN || p[y].first < wt_uxy) {
                    p[y] = {wt_uxy, x};
                    if(y == v) continue;
                    que.push({y, wt_uxy});
                }
            }
        }
        
        return p;
    }
    
    /*   max
        d  (u, v) - Maximum Path Distance function
         G
        the maximum distance from u to v by a path in the graph G.
        
        defined as:
            max                      max
           d  (u, v) := { l(p), p ϵ Π     and v ϵ Reach (u)
            G           {            u->v              G    
                        { -∞,   v ∉ Reach (u)
                                         G
    */
    int dMax_G(int u, int v) {
        auto reachU = Reach_G(u);
        
        // v ∉ Reach (u)
        //          G
        if(reachU.find(v) == reachU.end())
            return INT_MIN; // -∞
        
        auto pimax_uv = PImax_uv(u, v);
        int w = pimax_uv[v].first;
        
        return w;
    }
    
    
    /*
        V*(u) - Optimal Value function
        tuple of longest distances from u to every vertex v in graph G.
            
        defined as:     max
            V*(u) := ( d  (u, v) )
                        G         v ϵ V
    */
    vector<int> V_star(int u) {
        vector<int> d_uV(V, INT_MIN);
        d_uV[u] = 0;
        
        for(int v=0; v<V; v++) {
            if(v==u) continue;
            d_uV[v] = dMax_G(u, v);
        }
            
        return d_uV;
    }
    
  public:

    vector<int> maximumDistance(vector<vector<int>> edges, int v, int e, int src) {
        V = v;
        GammaPlus_G.resize(V);
        
        for(auto& e: edges) {
            int u = e[0], v = e[1], wt = e[2];
            GammaPlus_G[u].push_back({v, wt}); // only u -> v since directed graph G
        }
        
        return V_star(src);
    }
};


void read_line(stringstream& ss) {
    string line;
    getline(cin, line);
    ss.clear();
    ss.str(line);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	stringstream ss;
    
	int t;
	read_line(ss);
	ss >> t;
	
	Solution sol;

	while(t--) {
        int n, m, s;
        
        read_line(ss);
        ss >> n >> m >> s;
        
        vector<vector<int>> edges;
        
        for(int i=1; i<=m; i++) {
            int u, v, w;
            read_line(ss);
            while(ss >> u >> v >> w)
                edges.push_back({u, v, w});
        }

        
	    auto dist = sol.maximumDistance(edges, n, m, s);
	    
	    cout << "distance[] = [";
	    for(int i=0; i<dist.size(); i++) {
	        if(dist[i] == INT_MIN) cout << "INF";
	        else cout << dist[i];
	        cout << (i==dist.size()-1 ? "" : ",");
	    }
	    cout << "]\n";
	}

    return 0;
}
