#include <bits/stdc++.h>
using namespace std;

int maximalWaterVol(int n, int m, vector<vector<int>>& heights) {
    // {height, (i, j)}
    using P = pair<int, pair<int, int>>;
    
    const vector<pair<int, int>> directions = {
        {-1, 0}, // left
        {1, 0}, // right
        {0, -1}, // up
        {0, 1} // down
    };
    
    auto inBounds = [&](int i, int j) {
        return (i>=0 && i<n && j>=0 && j<m);
    };
    
    // min-heap sorted by height of the cuboid
    priority_queue<P, vector<P>, greater<P>> pq;
    vector<vector<bool>> visited(n,
                                vector<bool>(m, false));
    
    //Step-1: Push all boundary cells in PQ
    for(int j=0; j<m; j++) { // adding top & bottom row
        pq.push({ heights[0][j], {0, j} });
        visited[0][j] = true;
        
        pq.push({ heights[n-1][j], {n-1, j} });
        visited[n-1][j] = true;
    }
    
    for(int i=0; i<n; i++) { // adding left & right column
        pq.push({ heights[i][0], {i, 0} });
        visited[i][0] = true;
        
        pq.push({ heights[i][m-1], {i, m-1} });
        visited[i][m-1] = true;
    }
    
    //Step-2: Pop from PQ and check all adjacent neighbour cells
    // if the height(adjacent cell) < height(current cell) then water puddles can be formed
    int water = 0; // total volume of water puddles i.e how much water is added
    
    while(!pq.empty()) {
        auto p = pq.top();
        pq.pop();
        
        int h = p.first;
        int i = p.second.first, j = p.second.second;
        
        // moving in respective directions from (i, j)
        // left, right, up and down
        for(auto& dir: directions) {
            int i_ = i + dir.first; // i'
            int j_ = j + dir.second; // j'
            
            if (inBounds(i_, j_) && !visited[i_][j_]) {
                // adding needed water if heights(i', j') > heights(i, j)
                water += max(0, h - heights[i_][j_]);
                
                // pushing greater water level height (possibly height(i, j))
                int hmax = max(h, heights[i_][j_]);
                pq.push({ hmax, {i_, j_} });
                visited[i_][j_] = true;
            }
        }
    }
    
    return water;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
	int t;
	cin >> t;
	
	while(t--) {
	    int n, m;
	    cin >> n >> m;
	    
	    vector<vector<int>> heights(n,
	                                vector<int>(m));
	    
	    for(int i=0; i<n; i++) {
	        for(int j=0; j<m; j++)
	            cin >> heights[i][j];
	    }
	    
	    int vol = maximalWaterVol(n, m, heights);
	    cout << vol << "\n";
	}

    return 0;
}
