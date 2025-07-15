#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& nums) {
    const int n = nums.size();

    int candidateIdx = -1;
    int justgtCandidateIdx = -1; // just greater candidate index

    // find 1st decreasing element from right
	// as this is the number from which we need to move to higher number
    for(int i=n-1; i>0; i--) {
        if(nums[i] > nums[i-1]) {
            candidateIdx = i-1;
            break;
        }
    }

    if (candidateIdx != -1) {
        // find element just greater than candidate
        justgtCandidateIdx = candidateIdx;

        for(int i=n-1; i>=candidateIdx; i--) {
            if (nums[i] > nums[candidateIdx]) {
                justgtCandidateIdx = i;
                break;
            }
        }
            
        // swap both their positions for next permutation
		// by swaping we're going to the just greater number than the number which is original array (nums)
        swap(nums[candidateIdx], nums[justgtCandidateIdx]);
    }

    // reverse the subarray after candidate's index
	// Why? because now the greater element i.e candidate is at higher weighted position
	// so by reversing we make sure that the position of candidate goes to lower weighted position (possibly unit place)
    reverse(nums.begin()+candidateIdx+1, nums.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for(int& a: arr) cin >> a;
    
    nextPermutation(arr);
    
    cout << "[";
    for(int i=0; i<n; i++) {
        cout << arr[i];
        if(i<n-1) cout << ", ";
    }
    cout << "]\n";
    
    return 0;
}
