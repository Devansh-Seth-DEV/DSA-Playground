/**
 * Header files to include
 * <vector> for std::vector
 * <set> for std::set
 * <climits> for INT_MAX
 */

vector<int> dijkstra(const vector<vector<pair<int, int>>>& adj,
                    const int src) {
    const int V = adj.size();
    vector<int> distance(V, INT_MAX);
    set<pair<int, int>> minHeap;

    distance[src] = 0;  // distance from source to source is 0
    minHeap.insert({0, src}); // insert {wt: 0, v: src} in minHeap

    while(!minHeap.empty()) {
        auto& top = *minHeap.begin();
        int u = top.second, wt = top.first;
        minHeap.erase(top);

        for(const auto& node: adj[u]) {
            int v = node.first, w = node.second;
            int d = wt + w; // total distance from (src --> u) + (u --> v)
                
            if (d<distance[v]) {
                /* Why this check ?
                   if distance[v] is not INFINITY that means
                   {distance[v], v} is present in minHeap
                   but now we get even more shorter path i.e {d, v}
                   so we'll remove the greater path from the minHeap so that we'll
                   not process that path in future because it'll give greater values
                */
                if (distance[v] != INT_MAX)
                    minHeap.erase({distance[v], v});
                distance[v] = d;
                minHeap.insert({d, v});
            }
        }
    }

    return distance;
}
