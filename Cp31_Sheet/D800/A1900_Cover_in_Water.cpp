#include <bits/stdc++.h>
using namespace std;

void boostIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

class Solution {
public:
    static void runTestCases() {
        int cases;
        cin >> cases;
        
        while (0 != cases--) {
            int n;
            cin >> n;
            
            string cells;
            cin >> cells;
            
            int minActions = solve(n, cells);
            cout << minActions << "\n";
        }
    }
    
    static int solve(int n, string cells) {
        bool is3InARowEmpty = false;
        int emptyCellCount = 0;
        
        for(int i=0; i<n; i++) {
            // count total empty cells
            if ('.' == cells[i]) emptyCellCount++;
            
            // check for 3 consecutive cells
            if (i>=2 &&
                '.' == cells[i-2] && 
                '.' == cells[i-1] && 
                '.' == cells[i])
                is3InARowEmpty = true;
        }
        
        return (is3InARowEmpty ? 2 : emptyCellCount);    
    }
};

int main() {
    boostIO();
    Solution::runTestCases();
    return 0;
}
