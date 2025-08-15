#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        arr[1], arr[2], ..., arr[n]
        sum     (target)
*/

class Solution {
    int V_bar[201][10001]; // stores computed answers for F(i, j)
    bool chi[201][10001];  // true if V̄(i, j) is defined (computed & stored)
    
    vector<int> v;
    
    /*
        F(i, T) - Feasibility function
        indicating whether a subset sum of T is achievable from first i items.
        
        where:
        F(i, T) = { True,                       T = 0
                  { False,                      i = 0
                  { F(i-1, T) v F(i-1, T-v ),   T ≥ v
                  {                       i          i
                  { F(i-1, T),                  T < v
                                                     i
    */
    int F(int i, int T) {
        if(chi[i][T]) return V_bar[i][T];
        
        if(T==0) return true;
        if(i==0) return false;
        
        chi[i][T] = true;
        if(T < v[i-1])
            // skip v  as its more that T
            //       i
            
            return V_bar[i][T] = F(i-1, T);
        
        // check if we can get true both from skiping v  and picking it
        //                                             i
        
        return V_bar[i][T] = F(i-1, T) | F(i-1, T-v[i-1]);
        //                      skip   or      pick
    }
    
 public:

    bool isSubsetSum(vector<int>& arr, int sum) {
        v = std::move(arr);
        int n = v.size();
        
        for(int i=0; i<=200; i++)
            for(int j=0; j<=10000; j++)
                chi[i][j] = false;
        
        // indicates whether a subset sum of T is achievable from first n items.
        return F(n, sum);
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
	    int sum, nums;
	    vector<int> arr;
	    
	    read_line(ss);
	    while(ss >> nums)
	        arr.push_back(nums);
	        
	    read_line(ss);
	    ss >> sum;
	        
	    bool flag = sol.isSubsetSum(arr, sum);
	    cout << (flag ? "true" : "false") << "\n";
	}

    return 0;
}
