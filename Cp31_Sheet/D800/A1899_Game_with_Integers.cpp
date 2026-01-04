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
        if (!(cin >> testCases)) return;
        
        while(testCases--) solve();
    }

    /**
     * @brief Interface Layer: Handles data ingestion and output dispatch.
     */
    static void solve() {
        // 1. Ingest input parameters
        int n;
        if (!(cin >> n)) return;

        // 2. Execute computational logic
        auto result = process(n);

        // 3. Dispatch result to output stream
        cout << result << "\n";
    }

    /**
     * @brief Engine Layer: Pure logic for a single test case unit.
     * @param n Input parameter (Update signature as per problem)
     * @return Processed result (Update return-type as per problem)
     */
    static string process(int n) {
        string result;
        
        bool isVanyaWon = ((n+1)%3 == 0 || (n-1)%3==0);
        result = isVanyaWon ? "First" : "Second";
        
        return result;
    }
};

int main() {
    fastIO();
    Solver::execute();
    return 0;
}
