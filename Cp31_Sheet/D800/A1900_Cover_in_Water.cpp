#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Optimizes C++ I/O operations by desyncing with 
 *        stdio and untying cin from cout.
 */
inline void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class Solver {
public:
    /** @brief Entry point for handling multiple test cases. */
    static void execute() {
        int testCases = 1;
        // Comment this out for single test case problems
        cin >> testCases;
        while(testCases--)  solve();
    }
    
    
    /**
     * @brief Handles the reading of the input unit and printing
              the result.
     */
    static void solve() {
        // 1. Read input parameters
        int n;
        cin >> n;
        
        string cells;
        cin >> cells;
        
        // 2. Process logic
        auto result = process(n, cells);
        
        // 3. Output result
        cout << result << "\n";
    }
    
    
    /** @brief Core logic for a single test case unit. */
    static int process(int n, string cells) {
        // Local variables
        int result;
        bool is3InARowEmpty = false;
        int emptyCellCount = 0;
        
        // Implementation Logic Here
        for(int i=0; i<n; i++) {
            if (cells[i] == '.') emptyCellCount++;
            if (i>=2 &&
                cells[i-2] == '.' &&
                cells[i-1] == '.' &&
                cells[i] == '.') is3InARowEmpty = true;
        }
        
        result = is3InARowEmpty ? 2 : emptyCellCount;
        return result;
    }
};

int main() {
    fastIO();
    Solver::execute();
    return 0;
}
