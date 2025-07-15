#include <bits/stdc++.h>
using namespace std;

pair<int, int> twoSum2(vector<int>& arr, int target) {
    // since the arr is sorted we can use 2 pointers approach
    int l=0, r=arr.size()-1;
    
    // if sum < target move l++
    // if sum > target move r--
    // if sum == target return (l, r) 1-based
    // else return (-1, -1) no such pair exists
    while(l<r) {
        int sum = arr[l] + arr[r];
        if (sum < target) l++;
        else if (sum > target) r--;
        else if (sum == target)
            return {l+1, r+1};
    }
    
    return {-1, -1};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, t;
	cin >> n >> t;
	
	vector<int> arr(n);
	for(int& a: arr) cin >> a;
	
	pair<int, int> range = twoSum2(arr, t);
	if (range.first > 0 && range.second > 0)
	    cout << "[" << range.first << ", " << range.second << "]\n";
	else cout << "No pair found\n";
	
	return 0;
}
