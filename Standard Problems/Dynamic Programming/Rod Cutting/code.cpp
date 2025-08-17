#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        price[1], price[2], ..., price[n]
*/

class Solution {
    /*
        Let,
            1. n be the size of the rod in inches
            2. i be the length of a piece of the rod in inches.
            3. m be the number of cuts on the rod.
        such that
            i,n,m ϵ ℤ+ and 1 ≤ m <n
    */
    int n;

    /*
        Let, P be the set of prices for all possible piece lengths, defined as:
        
                P := {P ,P ,...,P }, where P  is the price of a piece of length i inches.
                       1  2      n          i
    */
    int* P;
    
    /*
        Let, V̄ be the storage vector, which represents the maximum cost of piece of length i inches
        defined as:
        
                V̄(i) := V*(i)
            
        and , χ (chi) be the indicator function which represents that we've already computed V̄
        defined as:
        
                χ(i) :=   { true,   V̄(i) is defined
                          { false,  otherwise
    */
    int VBar[1001];
    bool chi[1001];

    
    /*
        Define the cost function C(i) as:
            
                C(i) := { 0,   i = 0
                        { P  , otherwise
                           i   
            
            where P  is the total price of piece of length i inches.
                   i
    */
    int C(int i) {
        if (i==0) return 0;
        return P[i-1];
    }
    
    
    /*
        Now, let V*(n) be the optimal value function, which represents the maximum value obtainable by cutting the rod of n inches and selling the pieces.
        defined as:
        
                V*(n) :=  { V̄(k),                      χ(k) = true
                          { max       C(k) + V*(n-k),  otherwise
                            k ϵ [1,n]  
                              
            where:
                C(k) - is cost of cutting piece of length k inches
                V*(n-k) - cost of cutting the remaining piece of length n-k inches
    */
    int VStar(int n) {
        if(n<=0) return 0;
        
        if(chi[n]) return VBar[n];
        
        chi[n] = true;
        int max_n = 0;
        for(int k=1; k<=n; k++)
            max_n = max(max_n, C(k) + VStar(n-k));
            
        return VBar[n] = max_n;
    }
    
public:

    int cutRod(vector<int> &price) {
        n = price.size();
        P = price.data();
        
        for(int i=0; i<=n; i++)
            chi[i] = false;
            
        return VStar(n);
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
        vector<int> price;
        
        read_line(ss);
        int num;
        while(ss >> num)
            price.push_back(num);
        
	    auto res = sol.cutRod(price);
	    cout << res << "\n";
	}

    return 0;
}
