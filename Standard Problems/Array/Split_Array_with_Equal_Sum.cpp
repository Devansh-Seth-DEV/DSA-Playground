#include <bits/stdc++.h>
using namespace std;

int canSplit(vector<int>& arr) {
    int totalSum = accumulate(arr.begin(), arr.end(), 0);
    int prefix = 0;
    
    // check until n-1 (1-based) to ensure both parts are non-empty
    // substract the prefix sum from the total sum to get suffix sum
    for(int i=0; i<arr.size()-1; i++) {
        prefix += arr[i];
        int suffix = totalSum - prefix;
        if (prefix == suffix) return true;
    }
    
    return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for(int& a: arr) cin >> a;
	
	bool res = canSplit(arr);
	cout << (res ? "YES" : "NO") << "\n";
	
	return 0;
}
