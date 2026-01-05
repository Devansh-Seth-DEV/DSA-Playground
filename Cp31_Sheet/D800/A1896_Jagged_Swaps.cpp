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
        
        while(testCases--) solve();
    }

    /**
     * @brief Interface Layer: Handles data ingestion and output dispatch.
     */
    static void solve() {
        // 1. Ingest input parameters
        int n;
        cin >> n;
        
        int arr[11] = {0};
        for(int i=0; i<n; i++) cin >> arr[i];

        // 2. Execute computational logic
        auto result = process(n, arr);

        // 3. Dispatch result to output stream
        cout << result << "\n";
    }

    /**
     * @brief Engine Layer: Pure logic for a single test case unit.
     * @param n Input parameter (Update signature as per problem)
     * @return Processed result (Update return-type as per problem)
     */
    static string process(int n, int arr[]) {
        string result;
        bool isSortPossible = true;
        
        int i=1;
        while (i<n-1) {
            // if arr[0] > arr[1] then we cannot swap arr[0]
            // because we can only swap values (arr[1]:arr[n-2])
            if (arr[0] > arr[1]) {
                isSortPossible = false;
                break;
            }
            
            if (arr[i-1] < arr[i] && arr[i] > arr[i+1]) {
                // swap (arr[i], arr[i+1])
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                
                // recheck the condition arr[i-1] < arr[i]
                // if not true, then apply swap logic on i-1 first
                // otherwise normally move the i forward
                i += (arr[i-1] > arr[i]) ? -1 : 1;
            } else i++;
        }
        
        result = isSortPossible ? "YES" : "NO";
        return result;
    }
};

int main() {
    fastIO();
    Solver::execute();
    return 0;
}
