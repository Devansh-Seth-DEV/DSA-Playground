#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        W   (knapsack capacity)
        val[1], val[2], ..., val[n]
        wt[1], wt[2], ..., wt[n]
	    
    Constraints:
        2 ≤ |val| = |wt| ≤ 10³
        1 ≤ W ≤ 10³
        1 ≤ val[i], wt[i] ≤ 10³
*/

class Solution {
  	/*
    	V̄(i, W) - Memoization Vector, defined as:
	
	        V̄(i, W) := V*(i, W) once it has been evaluated

		χ(i, W) - Indicator function
		track whether V̄(i, W) has already been computed, defined as:
  
  			χ(i, W) := { true, 	  	V̄(i, W) is defined
	                   { false,		otherwise
  	*/
	int V_bar[1001][1001];
  	bool chi[1001][1001];
	vector<int> val, wt;

    
    /*
        C(i, W) - Cost function (cost obtained by picking item i given capacity W)
        where:
            C(i, W) = { 0,         wt[i] > W
                      { val[i],    otherwise
    */
    int C(int i, int W) const {
        return (wt[i-1]>W) ? 0 : val[i-1];
    }
    
    /*
        W'(i, W) - Residual capacity function (capacity left after picking item i)
        where:
            W'(i, W) = { W,         wt[i] > W
                       { W-wt[i],   otherwise
    */
    int W_prime(int i, int W) const {
        return (wt[i-1]>W) ? W : W-wt[i-1];
    }
    
    /*
        V*(i, W) - Value function (best achievable value with items val[i] ... val[1] and capacity W)
        where:
            V*(i, W) = { 0,                                                 i=0 or W=0
                       { max ( C(i, W) + V*(i-1, W'(i, W)), V*(i-1, W) ),   otherwise
    */
    int V_star(int i, int W) {
        if (i==0 || W==0) return 0;
        if (chi[i][W]) return V_bar[i][W]; // already computed
        
        chi[i][W] = true;
        return V_bar[i][W] = max(C(i, W) + V_star(i-1, W_prime(i, W)),
                                 V_star(i-1, W));
    }

public:
	int knapsack(int W, vector<int> &val, vector<int> &wt) {
        this->val = std::move(val);
        this->wt = std::move(wt);
        
        int n = this->val.size();
        
        for(int i=0; i<=n; i++)
            for(int j=0; j<=n; j++)
                chi[i][j] = false;
        
        // best achievable value from val[n] ... val[1] with capacity W
        return V_star(n, W);
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
	    int W, nums;
	    vector<int> val, wt;
	    
	    read_line(ss);
	    ss >> W;
	    
	    read_line(ss);
	    while(ss >> nums)
	        val.push_back(nums);
	        
	    read_line(ss);
	    while(ss >> nums)
	        wt.push_back(nums);
	        
	    int maximized = sol.knapsack(W, val, wt);
	    cout << maximized << "\n";
	}

    return 0;
}
