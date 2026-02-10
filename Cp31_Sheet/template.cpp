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
 * @brief Checks whether the given value is even or not
 * 
 * @param val The value to be check
 * @return Returns true if given value is even, otherwise false.
 */
inline bool iseven(long long val) {
    return (val&1)==0;
}

/**
 * @brief Compares and tells whether both the number has same parity or not.
 * 
 * @param a First number to check parity of
 * @param b Second number to check parity of
 * @return Returns true if both numbers have same parity, otherwise false.
 */
inline bool isSameParity(long long a, long long b) {
    return iseven(a) == iseven(b);
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
        for (size_t i = 0; i < vec.size(); ++i)
            print(vec[i], 
                  i+1 < vec.size() ? " " : "");
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


    /**
     * @brief Prints a std::pair.
     *
     * The elements of the pair are printed sequentially:
     *  - First element
     *  - A single space separator
     *  - Second element
     *
     * Both elements are printed recursively using the appropriate
     * `print()` overload, allowing support for nested types such as
     * vectors, arrays, or other pairs.
     *
     * Example output:
     *  - pair<int, int>        -> "1 2"
     *  - pair<int, string>     -> "5 hello"
     *  - pair<int, vector<int>> -> "3 1 2 3"
     *
     * @tparam X Type of the first element
     * @tparam Y Type of the second element
     * @param p Pair to print
     * @param end Output terminator (default: newline)
     *
     * @note Formatting is space-separated without surrounding
     *       parentheses, matching common competitive programming
     *       output conventions.
     *
     * @note The output terminator is applied only after the second
     *       element, ensuring no extra whitespace.
     */
    template <typename X, typename Y>
    void print(const pair<X, Y>& p, const char* end = "\n") {
        print(p.first, " ");
        print(p.second, end);
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
        int n;
        cin >> n;
 
        // 2. Execute computational logic
        auto result = process(n);
 
        // 3. Dispatch result to output stream
        printer.print(result);
    }
 
    /**
     * @brief Engine Layer: Pure logic for a single test case unit.
     * @param n Input parameter (Update signature as per problem)
     * @return Processed result (Update return-type as per problem)
     */
    int process(int n) {
        int result = 0;
                        
        // --- Implementation Logic Start ---
        
        // --- Implementation Logic End ---
        
        return result;
    }
};

int main() {
    fastIO();
    
    Solver solver;
    solver.execute();
    
    return 0;
}