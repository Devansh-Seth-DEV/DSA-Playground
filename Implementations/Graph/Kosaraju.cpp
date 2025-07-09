void toposort(int u, vector<vector<int>>& adj,
        vector<bool>& visited,
        stack<int>& st) {
    visited[u] = true;
            
    for(int& v: adj[u]) {
    	if (!visited[v])
        	toposort(v, adj, visited, st);
    }
            
    st.push(u);        
}
    
void dfs(int u, vector<vector<int>>& adj,
        vector<bool>& visited) {
    visited[u] = true;
            
    for(int& v: adj[u]) {
        if(!visited[v])
            dfs(v, adj, visited);
    }
}
    
int kosaraju(vector<vector<int>> &adj) {
    const int V = adj.size();
    stack<int> st;
    vector<bool> visited(V, false);
        
    // creating a topological order
    for(int u=0; u<V; u++) {
        if (!visited[u])
            toposort(u, adj, visited, st);
    }
        
    // making a reversed graph
    vector<vector<int>> adjRev(V);
    for(int u=0; u<V; u++) {
        for(int& v: adj[u]) {
            adjRev[v].push_back(u);
        }
    }
        
    // calling dfs based on stack order
	// for getting the count of strongly connected components
    visited = vector<bool>(V, false);
    int scc_count = 0;
        
    while(!st.empty()) {
        int u = st.top();
        st.pop();
            
        if(!visited[u]) {
            dfs(u, adjRev, visited);
            scc_count++;
        }
    }
        
    return scc_count;
}
