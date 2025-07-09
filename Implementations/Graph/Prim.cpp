int prim(const int V, const vector<vector<int>>& edges) {
	vector<vector<int>> adj(V);

  	// creating adjacency list from edges
  	// where u --> v with weigth wt
	for(auto& e: edges) {
    	int u = e[0], v = e[1], wt = e[2];
    	adj[u].push_back({v, wt});
		adj[v].push_back({u, wt});
  	}

  	using P = pair<int, int>;
  	// min heap {wt, v}
	// denotes the edge from u --> v with weight wt
  	priority_queue<P, vector<P>, greater<P>> pq;

  	vector<bool> visited(V, false);
  	int span_sum = 0; // min-spanning sum
  	pq.push({0, 0}); // wt = 0 from 0 --> 0

  	while(!pq.empty()) {
    	auto top = pq.top();
    	int wt = top.first, u = top.second;
    	pq.pop();

		// if u is visited then
		// already the smallest weighted path is chosen
		// so not taking any of its adjacent path again
    	if(visited[u]) continue;

		span_sum += wt;
		visited[u] = true;

    	for(auto& e: adj[u]) {
        	int v = e[0], wt = e[1];
			if(!visited[v])
				pq.push({wt, v});
		}
  	}

	return span_sum;
}
