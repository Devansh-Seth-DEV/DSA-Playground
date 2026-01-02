#include <bits/stdc++.h>
using namespace std;

inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int solve(int n, int x, int stations[]) {
    int maxDistToCover = stations[0];
    
    for(int i=1; i<n; i++) {
        int distToCover = stations[i] - stations[i-1];
        if (distToCover > maxDistToCover)
            maxDistToCover = distToCover;
    }
    
    int roundTripNX = 2 * (x-stations[n-1]);
    if (roundTripNX > maxDistToCover)
        maxDistToCover = roundTripNX;
        
    int minGasVolNeeded = maxDistToCover;
    return minGasVolNeeded;
}

void runTestCases() {
    int totalTestCases;
    int stations[101] = {0};
    
    cin >> totalTestCases;
    
    while(0 != totalTestCases--) {
        int n, x;
        
        cin >> n >> x;
        for(int i=0; i<n; i++) cin >> stations[i];
        
        int minGasVol = solve(n, x, stations);
        
        cout << minGasVol << "\n";
    }
}

int main() {
    fastIO();
    runTestCases();
    return 0;
}
