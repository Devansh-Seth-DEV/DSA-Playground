#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        m n
*/

class Solution {
    int V_bar[100][100]; // stores the calculated value of δ(x, y)
    bool chi[100][100];  // tells if v̄(x, y) is already calculated
    
    int M, N;
 
    /*
        Γ(x, y) = Successor function
        indicates the next valid point (x', y') to move from (x, y)
        
        defined as:
        Γ(x, y) = (x', y')
        
        where:
        (x', y') ∈ {(x+1, y), (x, y+1)} ∩ {0,...,N} × {0,...,M}
    */
    vector<pair<int, int>> Gamma(pair<int, int> p) {
        int x = p.first, y = p.second;
        
        vector<vector<int>> directions = {{1,0}, {0,1}};
        vector<pair<int, int>> p_; // neighbour cells to move p'
        
        for(auto& dir: directions) {
            int x_ = x + dir[0];
            int y_ = y + dir[1];
            if(x_ >= 0 && x_ < M &&
               y_ >= 0 && y_ < N)
                p_.push_back({x_, y_});
        }
        
        return p_;
    }
    
    /*
        δ(x, y) = State transition function or Step function
        indicates the dfs traversal starting from (x, y)
        
        defined as:
        δ(x, y) = { 1,          (x, y) = (m-1, n-1)
                  { v̄(x, y),    χ(x, y) = 1
                  { v̄(x', y'),  otherwise
                  
        
        where:
        v̄(x', y') = ∑ δ(p) | p ∈ Γ(x, y)
        χ(x, y) = indicator function 1 denotes (x, y) is visited, 0 otherwise
    */
    int delta(pair<int, int> p) {
        int x = p.first, y = p.second;
        pair<int, int> f = {M-1, N-1};
        
        if(chi[x][y]) return V_bar[x][y];
        if(p == f) return 1;
        
        chi[x][y] = true;
        auto p_ = Gamma(p);
        V_bar[x][y] = 0; // ∑ δ(p) | p ∈ Γ(x, y)
        
        for(auto& p: p_)
            V_bar[x][y] += delta(p);
        
        return V_bar[x][y];
    }
    
public:
    
    int numberOfPaths(int m, int n) {
        N = n; M = m;
        
        for(int i=0; i<M; i++)
            for(int j=0; j<N; j++)
                chi[i][j] = false;
                
        return delta({0, 0});
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
	    int m, n;
	    
	    read_line(ss);
	    ss >> m >> n;

	    int paths = sol.numberOfPaths(m, n);
	    cout << paths << "\n";
	}

    return 0;
}
