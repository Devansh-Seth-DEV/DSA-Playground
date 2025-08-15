#include <bits/stdc++.h>
using namespace std;

/*
    Input Format:
        t   (test cases)
        arr[1], arr[2], ..., arr[n]
*/

#define MAX_ARR_SIZE (int) 1e3
#define OFFSET 1

class Solution {
    vector<int> v;
    int N;
    
    int V_bar[MAX_ARR_SIZE][MAX_ARR_SIZE + OFFSET];  // computed value of V*(i, T)
    bool chi[MAX_ARR_SIZE][MAX_ARR_SIZE + OFFSET];   // true if V̄(i, T) is defined
 
    /*
        V*(i, T) = Optimal Value function
        indicates best achievable value/length with i items v[i] ... v[N-1] 
        with previous index T of i such that v[T] < v[i]
        
        More formally,
        V*(i, T) = { 0,                                 i >= N
                   { max(1 + V*(i+1, i), V*(i+1, T)),   T = -1 V v[T] < v[i]
                   { V*(i+1, T),                        otherwise
    */
    int V(int i, int T) {
        int t = T + OFFSET; // shift by offset to make -1 -> 0, 0 -> 1
        
        if (chi[i][t]) return V_bar[i][t];
        if(i>=N) return 0;
        
        chi[i][t] = true;
        if(T==-1 || v[T] < v[i])
            return V_bar[i][t] = max(1 + V(i+1, i), V(i+1, T));
            
        return V_bar[i][t] = V(i+1, T);
    }

 public:
    
    int lis(vector<int>& arr) {
        v = std::move(arr);
        N = v.size();
        
        for(int i=0; i<MAX_ARR_SIZE; i++)
            for(int j=0; j<MAX_ARR_SIZE; j++)
                chi[i][j] = false;
        
        // best achievable length from 0 to N-1 with previous index T = -1
        return V(0, -1);
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
	    int nums;
	    vector<int> arr;
	    
	    read_line(ss);
	    while(ss >> nums)
	        arr.push_back(nums);
	        
	    int lis = sol.lis(arr);
	    cout << lis << "\n";
	}

    return 0;
}
