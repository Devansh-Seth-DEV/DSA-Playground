#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        s
*/

class Solution {
    /*
        Let, w be a sequence of characters, w := w .w ...w , w ∈ Σ*
                                                  1  2    n
        
        Let, S be the set of positions, defined as
        
                S := (i ,i ,...,i ) ⊆ {1,2,...,n}
                       1  2      m
                
        then define the subsequence as
        
                w[S] := w(i ).w(i )...w(i )
                           1     2       m
    */
    const char* w;
    int n;
    
    
    /*
        Let, V̄ be the length of palindromic subsequence w[i..j] variable defined as:
        
                V̄(i, j) := |w[i..j]| where i,j ∈ {0,1,..,|w|-1}
                
        and, χ (chi) be the indicator function defined as:
        
                χ(i, j) :=   { true,   V̄ is defined
                             { false,  otherwise
    */
    int V_bar[1000][1000];
    bool chi[1000][1000];

    /*
        Now, to find the length of longest palindromic subsequence:
        
        Let, V*(i, j) be the longest palindromic subsequence length function
        defined as:
        
                V(i, j) := { V̄(i, j),                       χ(i,j) = true
                           { 0,                             i>j
                           { 1,                             i=j
                           { 2 + V*(i+1, j-1),              w[i] = w[j]
                           { max(V*(i+1, j), V*(i, j-1)),   otherwise
    */                              
    int V_star(int i, int j) {
        if(chi[i][j]) return V_bar[i][j];
        
        if (i>j) return 0;
        if (i==j) return 1;
        
        chi[i][j] = true;
        if(w[i] == w[j])
            return V_bar[i][j] = 2 + V_star(i+1, j-1);
        
        return V_bar[i][j] = max(V_star(i+1, j), V_star(i, j-1));
    }

 public:
    
    int longestPalinSubseq(string &s) {
        w = s.c_str();
        n = s.length();
        
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                chi[i][j] = false;
        
        // V*(0, |w|-1) will give the longest palindromic subsequence length
        // in sequence w[1..|w|]
        return V_star(0, n-1);
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
        string s;
        read_line(ss);
        ss >> s;
        
	    auto res = sol.longestPalinSubseq(s);
	    cout << res << "\n";
	}

    return 0;
}
