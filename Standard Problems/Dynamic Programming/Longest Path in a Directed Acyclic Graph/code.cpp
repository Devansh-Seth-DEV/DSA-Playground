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
        δ(u) - DFS traversal function
        traverse all the vertex in the graph G
        
        defined as:
            δ(u) := { ∅,                                    u ϵ visited
                    {                                             +
                    { visited <-- visited U {u} and δ(v),   ∀v ϵ Γ (u)
                                                                  G
    */
    void delta(int u,
               vector<bool>& visited,
               stack<int>& st) {
        visited[u] = true;
        
        for(auto& alpha_uv: GammaPlus_G[u]) {
            int v = alpha_uv.first;
            if(!visited[v])
                delta(v, visited, st);
        }
        
        st.push(u);
    }
    
    
    /*   
        τ  - Topological ordering function
         G
        gives the topological order of graph G.
        it maps vertices with positions/order
        
        defined as:
            τ  : V -~-> {1, 2, ..., |V|}
             G
            
            such that:           -1       -1
                ∀(u, v) ϵ E ==> τ  (u) < τ  (v)
                                 G        G
                here τ  is bijective ( -~-> ) i.e every vertex gets unique position 
                      G
                and all positions are used
                
                                          -1
        It returns the inverse of τ  i.e τ
                                   G      G
        such that:
             -1
            τ  (i) := vertex at position i in topological order of graph G
             G
    */
    vector<int> tau_G() {
        vector<bool> visited(V, false);
        stack<int> st;
        vector<int> tauInv_G;
        
        for(int u=0; u<V; u++) {
            if (!visited[u])
                delta(u, visited, st);
        }
        
        while(!st.empty()) {
            tauInv_G.push_back(st.top());
            st.pop();
        }
        
        return tauInv_G;
    }

    
    /*
        V*(u) - Optimal Value function
        tuple of longest distances from u to every vertex v in graph G.
            
        defined as:        (n)
            V*(u) := ( dist   (v) )
                           u       v ϵ V
        
        where:
        
            dist (v) - Distance vector
                u
            stores distance from u to v
        
                (0)
            dist   (v) := { 0,  v = u
                u         { −∞, otherwise
                          
            For k = 1, 2, ..., |V|
            Let v  be vertex with topological position k
                 k
                 
            defined as:
                       -1
                v  := τ  (k)
                 k     G
                                                  (k)
            Let updated distance at step k be dist   (z)
                                                  u
            defined as:
                    (k)                 (k-1)         (k-1)                         +
                dist   (z) := { max(dist     (z), dist     (v ) + w(v , z)),   z ϵ Γ  (v )
                    u         {         u             u      k       k              G   k
                              {
                              {     (k-1)
                              { dist     (z),                                   otherwise
                                    u
                              
             where:
                    (k-1)
                dist     (z) is distance vector before updating vertex v  (after k-1 iterations)
                    u                                                   k
                    
                    (k)
                dist   (z) is distance vector after processing v  (after k iterations)
                    u                                           k
    */
    vector<int> V_star(int u) {
        vector<int> dist_u(V, /* −∞ */ INT_MIN);
        dist_u[u] = 0;
        
        auto tauInv_G = tau_G();
        
        for(int k=0; k<V; k++) {
            int v_k = tauInv_G[k];
            if(dist_u[v_k] == INT_MIN) continue;
            
            for(auto& alpha_vz: GammaPlus_G[v_k]) {
                int z = alpha_vz.first;
                int wt_vz = alpha_vz.second;
                
                dist_u[z] = max(dist_u[z], dist_u[v_k] + wt_vz);
            }
        }
            
        return dist_u;
    }
    
public:

    vector<int> maximumDistance(vector<vector<int>> edges, int v, int e, int src) {
        V = v;
        GammaPlus_G.resize(V);
        
        for(auto& e: edges) {
            int u = e[0], v = e[1], wt = e[2];
            GammaPlus_G[u].push_back({v, wt}); // only u -> v since directed graph G
        }
        
        //tuple of longest distances from src to every vertex v in graph G.
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
