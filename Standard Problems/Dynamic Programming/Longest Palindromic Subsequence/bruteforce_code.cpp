#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        s
*/

class Solution {
    /*
        Let, w be a sequence of characters, w := w .w ...w
                                                  1  2    n
        
        Let, S be the set of positions, defined as
        
                S := (i ,i ,...,i ) ⊆ {1,2,...,n}
                       1  2      m
                
        then define the subsequence as
        
                w[S] := w(i ).w(i )...w(i )
                           1     2       m
        
        Let, u      be a subsequence between positions p and q (inclusive) defined as:
              p,q,S
        
                u      := w[S] | S ⊆ (p,p+1,...,q) with S strictly increasing
                 p,q,S
            
                         R
        Let, Ψ      and Ψ      be a subsequence and reverse subsequence respectively of any state k
              p,q,S      p,q,S
              
        defined as:
            
                Ψ      := { ∅,          q < p
                 p,q,S    { u     ,     q >= p
                            p,q,S
                           
                 R
                Ψ      := rev( Ψ      )
                 p,q,S          p,q,S


              (k)
        Let, Ψ      be the new subsequence when concatinating with w , defined as:
              p,q,S                                                 k
        
                 (k)                     (k-1)
                Ψ      := { w ,         Ψ      = ∅
                 p,q,S    {  k           p,q,S    
                          {
                          {              (k-1)
                          { w[S U {k}], Ψ      ≠ ∅ and k > max(S)
                                         p,q,S
    */
    string w;
    
    /*        
        Let, π( Ψ      ) be the length function, defined as:
                 p,q,S
                                                                        R
                π( Ψ      ) := { 0,             Ψ      = ∅ or Ψ      ≠ Ψ
                    p,q,S      {                 p,q,S         p,q,S    p,q,S
                               {
                               {                                         R
                               { | Ψ      |,    Ψ      ≠ ∅ and Ψ      = Ψ
                                    p,q,S        p,q,S          p,q,S    p,q,S
    */
    int pi(string& psi_pqS) {
        /* Ψ      = ∅
            p,q,S
        */
        if(psi_pqS.length()==0) return 0;
        
        /*           R
           Ψ      ≠ Ψ
            p,q,S    p,q,S
        */
        int i=0, j=psi_pqS.length()-1;
        while(i<j) {
            if(psi_pqS[i] != psi_pqS[j])
                return 0;
            i++; j--;
        }
        
        /*           R
           Ψ      = Ψ
            p,q,S    p,q,S
        */
        return psi_pqS.length();
    }
    
    /*
        Now, to find the length of longest palindromic subsequence:
        
                  (k)
        Let, V*( Ψ      ) be the longest palindromic subsequence length function
                  p,q,S
                  
        defined as:
        
                     (k)
                V*( Ψ      ) := { 0,                                                        k = 0
                     p,q,S      { π( Ψ      ),                                              k>|w|
                                {     p,q,S
                                {
                                {                        (k)
                                { max{ π( Ψ      ), V*( Ψ     , k+1 ), V*( Ψ     , k+1 ) }, otherwise
                                           p,q.S         p,q,S              p,q,S
            
            ∀k ϵ {1,2,...,|w|}
    */                              
    int V_star(string& psi_pqS, int k) {
        if(k==0) return 0;
        if(k > w.length()) return pi(psi_pqS);
        
        /*  (k)
           Ψ
            p,q,S
        */
        string psiK_pqS = psi_pqS + w[k-1];
        
        return max({pi(psi_pqS), V_star(psiK_pqS, k+1), V_star(psi_pqS, k+1)});
    }
    
public:
    
    int longestPalinSubseq(string &s) {
        w = s;
        string psi_pqS = "";
        
        // V*(∅, 1) will give the longest palindromic subsequence length
        // in sequence w fron 1...|w|
        return V_star(psi_pqS, 1);
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
