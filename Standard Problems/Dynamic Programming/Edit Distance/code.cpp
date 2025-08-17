#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        s1
        s2
*/

class Solution {
    /*
        Given 2 strings s and t such that s,t ∈ Σ* 
        where 
            Σ := {a,b,...,z}
            |s| = n is length of string s
            |t| = m is length of string t
                            
            and 1 ≤ n,m ≤ 10³
        
        Find: min{ k ∈ ℕ | ∃ ω , ..., ω ∈ Σ* : ω = s, ω = t  ∀i ∈ [1,k]  ω ~ ω    }
                              0         k        0      k                  i   i-1
                              
            where relation ~ is "one edit apart":
                ω ~ ω' iff ω' is obtained from ω by exactly one of:
                    - Insertion: insert one letter of Σ
                    - Deletion: delete one letter from ω
                    - Relacing: relace one letter of ω by another letter of Σ
    */
    const char *s, *t;
    int n, m;
    
    /*
        Let, V̄(i,j) - Memoization Table
        The minimum number of operations needed to convert s[i..n] into t[j..m]
        defined as:
        
            V̄(i,j) := V*(i,j) once it has been evaluated 

        χ(i,j) - Indicator function, defined as:
        
            χ(i,j) := { true,    V̄(i,j) is already computed
                      { false,   otherwise
    */
    int VBar[1001][1001];
    bool chi[1001][1001];
    
    /*
        Let, V*(i,j) - Optimal Value function
        The minimum number of operations needed to convert string s of length n, into t of length m
        
        Defined as:
            
                V*(i,j) := { m-j+1,                                        i>n
                           { n-i+1,                                        j>m
                           { V̄(i,j),                                       χ(i,j) = true
                           { V*(i+1,j+1),                                  s[i] = t[j]
                           { 1 + min{ V*(i,j+1), V*(i+1,j), V*(i+1,j+1) }, otherwise
                           
            where:
               - m-j+1: length of remaining string t
               - n-i+1: length of remaining string s
               - V*(i,j+1): means you're inserting letter t[j] before i
               - V*(i+1,j): means you're removing i-th letter from s
               - V*(i+1,j+1) from min: means you're replacing i-th letter of s with t[j]
    */
    int VStar(int i, int j) {
        if(i>n) return m-j+1; //length of remaining string t
        if(j>m) return n-i+1; //length of remaining string s
        if(chi[i][j]) return VBar[i][j];
        
        chi[i][j] = true;
        if(s[i-1] == t[j-1])
            return VBar[i][j] = VStar(i+1,j+1);
        
        return VBar[i][j] = 1 + min( {VStar(i,j+1), VStar(i+1,j), VStar(i+1,j+1)} );
    }
    
public:

    int editDistance(string& s1, string& s2) {
        s = s1.c_str(); n = s1.length();
        t = s2.c_str(); m = s2.length();
      
        for(int i=0; i<=n; i++)
            for(int j=0; j<=m; j++)
                chi[i][j] = false;
                
        return VStar(1, 1);
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
        ss >> s1;
        
        read_line(ss);
        ss >> s2;
        
	    auto res = sol.editDistance(s1, s2);
	    cout << res << "\n";
	}

    return 0;
}
