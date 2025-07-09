int find(const int u, vector<int>& parent) {
	if(parent[u] == u) return u;
	return parent[u] = find(u, parent);
}

bool unite(const int u, const int v,
		vector<int>& parent,
		vector<int>& size) {
	int pu = find(u, parent);
	int pv = find(v, parent);

	// if both have same parents
	// then no union operation is performed
	// returning false denoting operation not performed
	if (pu == pv) false;

	if (size[pu] >= size[pv]) {
		parent[pv] = pu;
		size[pu] += size[pv];
	} else {
		parent[pu] = pv;
		size[pv] += size[pu];
	}

	// returning true denotes union operation is performed
	return true;
}
