#include <bits/stdc++.h>
using namespace std;

int majorityElement(vector<int>& arr) {
    // using Boyer-Moore Voting Algorithm
    // idea behind this is make pairs of elements which are different
    // by doing this at the end only 1 element remains which don't have paring
    // and that element is majority element
        
    int count=0, candidate=-1;
    for(int num: arr) {
        if (count==0) candidate = num;
            
        // adding count of same element
        // this will be used to make pairs with different elements
        // if not same then remove one pair
        count += (num == candidate) ? 1 : -1;
    }
        
    return candidate;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> arr(n);
	for(int& a: arr) cin >> a;
	
	int majEle = majorityElement(arr);
	cout << majEle << "\n";
	
	return 0;
}
