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

/**
 * @brief Generic output utility for competitive programming.
 *
 * The Printer class provides a unified interface for printing
 * various data types to standard output. It supports:
 *  - Primitive types (int, double, etc.)
 *  - Boolean values (printed as YES / NO)
 *  - C-style strings and std::string
 *  - std::vector<T> (including nested vectors)
 *  - std::vector<bool> (specialized handling)
 *  - Built-in arrays of any dimension
 *
 * All print operations are recursive and automatically dispatch
 * to the correct overload using C++ overload resolution.
 *
 * @note Designed for competitive programming environments.
 * @note Trailing spaces are avoided in container outputs.
 */
class Printer {
public:
    /**
     * @brief Prints a generic value followed by a terminator.
     *
     * This overload is selected for any type supporting
     * the stream insertion operator (operator<<).
     *
     * @tparam T Type of the value to print
     * @param val Value to print
     * @param end Output terminator (default: newline)
     */
    template <typename T>
    void print(const T& val, const char* end="\n") {
        cout << val << end;
    }
    
    /**
     * @brief Prints a boolean value as "YES" or "NO".
     *
     * @param val Boolean value
     * @param end Output terminator (default: newline)
     */
    void print(bool val, const char* end="\n") {
        cout << (val ? "YES" : "NO") << end;
    }
    
    /**
     * @brief Prints a null-terminated C-style string.
     *
     * @param s Pointer to null-terminated string
     * @param end Output terminator (default: newline)
     */
    void print(const char* s, const char* end="\n") {
        cout << s << end;
    }
    
    /**
     * @brief Prints a std::string.
     *
     * @param s String to print
     * @param end Output terminator (default: newline)
     */
    void print(const string& s, const char* end="\n") {
        cout << s << end;
    }
    
    /**
     * @brief Prints elements of a std::vector.
     *
     * Elements are printed recursively and separated by spaces.
     * Trailing spaces are avoided.
     *
     * @tparam T Element type of the vector
     * @param vec Vector to print
     * @param end Output terminator (default: newline)
     */
    template <typename T>
    void print(const vector<T>& vec, const char* end="\n") {
        for (size_t i = 0; i < vec.size(); ++i)
            print(vec[i], 
                  i+1 < vec.size() ? " " : "");

        cout << end;
    }
    
    /**
     * @brief Prints a std::vector<bool>.
     *
     * This overload exists due to std::vector<bool>'s
     * bit-proxy specialization, ensuring correct boolean output.
     *
     * @param vec Vector of booleans
     * @param end Output terminator (default: newline)
     */
    void print(const vector<bool>& vec,
               const char* end="\n") {
        for (bool b : vec) print(b, " ");
        cout << end;
    }
    
    /**
     * @brief Prints a built-in array of fixed size.
     *
     * The array size is deduced at compile time.
     * Supports multi-dimensional arrays via recursion.
     *
     * @tparam T Element type
     * @tparam N Number of elements
     * @param arr Reference to the array
     * @param end Output terminator (default: newline)
     */
    template <typename T, size_t N>
    void print(const T (&arr)[N], const char* end = "\n") {
        for (size_t i = 0; i < N; ++i)
            print(arr[i],
                  i+1 < N ? " " : "");
        cout << end;
    }
    
    /**
     * @brief Prints a fixed-size character array safely.
     *
     * This overload is specifically designed to handle character arrays
     * that are NOT guaranteed to be null-terminated (i.e., not C-strings).
     *
     * Unlike `print(const char*)`, which assumes a null-terminated string
     * and may cause undefined behavior if none is present, this function
     * prints exactly N characters from the array.
     *
     * This prevents buffer over-reads when printing raw character buffers,
     * keys, grids, or fixed-length data.
     *
     * @tparam N Size of the character array
     * @param arr Reference to a character array of size N
     * @param end Output terminator (default: newline)
     *
     * @note String literals (e.g. "Hello") will still prefer the
     *       `print(const char*)` overload due to overload resolution,
     *       ensuring correct C-string behavior.
     *
     * @warning This function does NOT stop at '\\0'. All N characters
     *          are printed unconditionally.
     */
    template <size_t N>
    void print(const char (&arr)[N], const char* end = "\n") {
        for (size_t i = 0; i < N; ++i)
            print(arr[i],
                  i+1 < N ? " " : "");
        cout << end;
    }

};


class Solver {
private:
    Printer printer;
    
public:
    /** @brief Entry point for handling multiple test cases. */
    void execute() {
        int testCases = 1;
        // Comment this out for single test case problems
        cin >> testCases;
        
        while(testCases--) solve();
    }

    /**
     * @brief Interface Layer: Handles data ingestion and output dispatch.
     */
    void solve() {
        // 1. Ingest input parameters
        int n, k;
        cin >> n >> k;

        int arr[101] = {0};
        for(int i=0; i<n; i++) cin >> arr[i];
 
        // 2. Execute computational logic
        auto result = process(n, k, arr);
 
        // 3. Dispatch result to output stream
        printer.print(result);
    }
 
    /**
     * @brief Engine Layer: Pure logic for a single test case unit.
     * @return Processed result (Update return-type as per problem)
     */
    bool process(int n, int k, int (&arr)[101]) {
        bool result = false;
                
        for(int i=0; i<n; i++) {
            if (arr[i] == k) {
                result = true;
                break;
            }
        }
        
        return result;
    }
};

int main() {
    fastIO();
    
    Solver solver;
    solver.execute();
    
    return 0;
}