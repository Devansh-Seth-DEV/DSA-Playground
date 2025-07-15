#include <bits/stdc++.h>
using namespace std;

int trap(vector<int>& height) {
    const int n = height.size();
    vector<int> leftMax(n, INT_MIN); // stores the max value at left side of i-th index
    vector<int> rightMax(n, INT_MIN); // store the max value at right side of i-th index

    leftMax[0] = height[0]; // boundary element have no left
    rightMax[n-1] = height[n-1]; // boundary element have no right

    // filling left max values for all i from 1 to n-1
    for(int i=1; i<n; i++)
        // picking the maximum height between current bar & left max bar height
        leftMax[i] = max(height[i], leftMax[i-1]);
        
    // filling right max values for all i from n-2 to 0
    for(int i=n-2; i>=0; i--)
        // picking the maximum height between current bar & right max bar height
        rightMax[i] = max(height[i], rightMax[i+1]);

    int water = 0; // amount of water will trapped after rain
    for(int i=0; i<n; i++)
        // minimum of left & right maximum height bar will be upperbound till which
        // the water will be trapped also decrease the height of current bar if
        // current bar height is not equal to 0
        water += min(leftMax[i], rightMax[i]) - height[i];

    return water;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> height(n);
    for(int& h: height) cin >> h;
    
    int waterTrapped = trap(height);
    cout << waterTrapped << "\n";
    
    return 0;
}
