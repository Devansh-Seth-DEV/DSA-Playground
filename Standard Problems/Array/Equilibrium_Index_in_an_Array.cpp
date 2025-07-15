#include <bits/stdc++.h>
using namespace std;

int equilibrium(vector<int>& arr) {
    if(arr.size()==1)
        return 0;

    if(arr.size()==2)
        return -1;
        
    vector<int> sum(arr.size()); // precomputed prefix sum array
    sum[0] = arr[0];

	// pre-computing the prefix sum array
    for(int i=1; i<arr.size(); i++)
        sum[i] = sum[i-1]+arr[i];

	// if arr size >= 3
	// left sum is precomputed value of sum[i-1]
	// right sum is total arr sum - the current sum i.e sum[i]
	// if left & right sum is equal then return index
    for(int i=1; i<arr.size()-1; i++) {
        int leftSum = sum[i-1];
        int rightSum = sum[arr.size()-1] - sum[i];
        if(leftSum == rightSum)
            return i;
    }
    
    return -1; // no index found where left & right sum is equal
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for(int& a: arr) cin >> a;
	
	int idx = equilibrium(arr);
	cout << idx << "\n";
	
	return 0;
}
