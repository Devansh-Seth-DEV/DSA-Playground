#include <bits/stdc++.h>
using namespace std;

const vector<vector<int>> directions = {
    {-1, 0}, // up
    {0, -1}, // left
    {0, 1}, // right
    {1, 0} // down
};


int minTimesDressChange(vector<string>& city) {
    const int n = city.size();
    const int m = city[0].size();
    
    auto inBounds = [&](int i, int j) -> bool {
        return (i>=0 && i<n && j>=0 && j<m);
    };
    
    // if city have same dress code then no travel cose
    // else travel cost of 1 is needed
    auto travelCost = [&](int i, int j,
                        int i_, int j_) -> int {
        return city[i][j] != city[i_][j_];
    };
    
    
    deque<pair<int, int>> dq; // {i, j}
    vector<vector<int>> cost(n, vector<int>(m, INT_MAX));
    
    dq.push_front({0, 0}); // src distance
    cost[0][0] = 0; // cost of u --> u is 0
    
    // core logic:
    // 1. if Dress(i, j) == Dress(i', j') then the cost of travelling from (i, j) --> (i', j') is 0
    // 2. if Dress(i, j) != Dress(i', j') then the cost of travelling from (i, j) --> (i', j') is 1
    // cost(i', j') = 1 denotes that we'll have to change the dress before moving to (i', j')
    // cost(i', j') = 0 denotes that we don't have to change the dress before moving to (i', j')
    
    // now we'll run 0-1 BFS on this cost factor to find
    // the minimum cost it takes to reach (n-1, m-1)
    // Time Complexity: O(V+E)
    
    while(!dq.empty()) {
        auto f = dq.front(); dq.pop_front();
        int i = f.first, j = f.second;
        
        for(auto& dir: directions) {
            int i_ = i + dir[0]; // i'
            int j_ = j + dir[1]; // j'
            
            if(inBounds(i_, j_)) {
                // calculating total cost to reach (i', j') from (i, j)
                int w = travelCost(i, j, i_, j_);
                int newcost = cost[i][j] + w;
                
                // updating minimum cost to reach (i', j')
                if (newcost < cost[i_][j_]) {
                    cost[i_][j_] = newcost;
                    
                    if (w==0) dq.push_front({i_, j_}); // cost = 0 -> higher priority
                    else dq.push_back({i_, j_}); // cost = 1 -> lower priority
                }
            }
        }
    }
    
    return cost[n-1][m-1];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    
    for(int i=1; i<=t; i++) {
        int n, m;
        cin >> n >> m;
        
        vector<string> city(n);
        for(auto& s: city) cin >> s;
        cin.ignore();
        
        int changed = minTimesDressChange(city);
        cout << "Case " << i << ": " << changed << "\n";
    }
    
    return 0;
}
