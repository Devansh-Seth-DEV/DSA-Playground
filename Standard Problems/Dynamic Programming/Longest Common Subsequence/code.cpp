#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        s1 s2
*/

class Solution {
    /*
        Given 2 strings ω1 and ω2
        where:
            ω ϵ Σ*
            ω1[i] denotes element at index i in string ω1
            ω2[j] denotes element at index j in string ω2
            
            |ω| = length of string ω
            i ϵ {1, 2, ..., |ω1|}
            j ϵ {1, 2, ..., |ω2|}
    */
    string w1, w2;
    
    /*
       V̄(i, j) - storage function
       stores the computed value of V*(i, j)
       
       defined as:
            V̄(i, j) := V*(i, j)
    */
    int V_bar[1001][1001];
    
    /*
        χ(i, j) - Indicator function
        tells if we've already computed V̄(i, j)
        
        defined as:
            χ(i, j) :=  { 1,   V̄(i, j) is computed
                        { 0,   otherwise
        }
    */
    bool chi[1001][1001]; 
    
    /*
        V*(i,j) = optimal value function, which calculates longest common
             subsequence in strings ω1 and ω2 of length |ω1| and |ω2| respectively
        
        defined as:
            V*(i, j) := { 0,                            i ∉ {1, 2, ..., |ω1|}, j ∉ {1, 2, ...,|ω2|}
                        { 1 + V*(i-1, j-1),             ω1[i] = ω2[j]
                        { max(V*(i-1, j), V*(i, j-1)),  otherwise
    */
    int V_star(int i, int j) {
        // i ∉ {1, 2, ..., |ω1|}, j ∉ {1, 2, ..., |ω2|}
        if(i<1 || i>w1.length() || j<1 || j>w2.length())
            return 0;
        
        // χ(i, j) = 1 means V̄(i, j) is computed so return the stored value
        if(chi[i][j]) return V_bar[i][j];
        
        chi[i][j] = true;
        if(w1[i-1] == w2[j-1]) // ω1[i] = ω2[j]
            return V_bar[i][j] = 1 + V_star(i-1, j-1);
        
        // otherwise
        return V_bar[i][j] = max(V_star(i-1, j), V_star(i, j-1));
    }
    
public:

    int lcs(string &s1, string &s2) {
        w1 = std::move(s1);
        w2 = std::move(s2);
        
        int n = w1.length();
        int m = w2.length();
        
        for(int i=0; i<=n; i++)
            for(int j=0; j<=m; j++)
                chi[i][j] = false;
        
        return V_star(n, m);
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
        string s1, s2;
        
        read_line(ss);
        ss >> s1 >> s2;
        
	    auto res = sol.lcs(s1, s2);
	    cout << res << "\n";
	}

    return 0;
}
