# 🚀 DSA-Playground

<p align="left">
   <img src="https://img.shields.io/badge/Laboratory-DSA--Playground-00b4d8?style=for-the-badge&logo=rocket&logoColor=white" alt="Repo Name">
   &nbsp;
   <img src="https://img.shields.io/badge/Core-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17">
   &nbsp;
   <img src="https://img.shields.io/badge/Engine-Optimized-success?style=for-the-badge&logo=cpu&logoColor=white" alt="Optimized Engine">
   &nbsp;
   <img src="https://img.shields.io/badge/Architecture-Triple--Layer-blueviolet?style=for-the-badge" alt="Architecture">
   &nbsp;
   <img src="https://img.shields.io/badge/Layout-vEB--Optimized-ffca28?style=for-the-badge&logoColor=black" alt="vEB Layout">
   &nbsp;
   <img src="https://img.shields.io/badge/Status-In_Development-brightgreen?style=for-the-badge" alt="Status"/>
   &nbsp;
   <img src="https://img.shields.io/badge/Platform-Codeforces-445f9d?style=for-the-badge&logo=codeforces&logoColor=white" alt="Platforms"/>
</p>

A high-performance laboratory for mastering Data Structures and Algorithms. This repository features industrial-grade templates, optimized competitive programming solutions, and structured implementations.

## 🗺️ Repository Map
> [!TIP]
> Click on the icons or headers to navigate to the specific modules.

<table width="100%">
   <tr>
      <td width="50%" valign="top">
         <h3>🎯 <a href="./Cp31_Sheet/">CP31-Sheet</a></h3>
         <p>Progressive problem-solving through the CP-31 curated list.</p>
         <ul>
            <li><code>D800 - D1200</code>: Foundation</li>
            <li><code>D1300 - D1900</code>: Intermediate/Advanced</li>
         </ul>
      </td>
      <td width="50%" valign="top">
         <h3>⚙️ <a href="./Implementations/">Implementations</a></h3>
         <p>Modular, reusable templates for core DSA.</p>
         <ul>
            <li><b>Graphs:</b> Shortest Paths, MST, Flow</li>
            <li><b>Trees:</b> Segment Trees, Splay Trees</li>
         </ul>
      </td>
   </tr>
    
   <tr>
      <td width="50%" valign="top">
         <h3>🧩 <a href="./Problems/">Solved Problems</a></h3>
         <p>Collection of solutions from various OJs.</p>
         <ul>
            <li><code>LeetCode</code> / <code>SPOJ</code> / <code>Timus</code></li>
            <li><code>Archived</code>: Legacy/Offline problems</li>
         </ul>
      </td>
      <td width="50%" valign="top">
         <h3>📚 <a href="./Standard%20Problems/">Standard Problems</a></h3>
         <p>The "Must-Do" classics categorized by topic.</p>
         <ul>
            <li><code>Dynamic Programming</code> patterns</li>
            <li><code>Array</code> manipulation & Logic</li>
         </ul>
      </td>
   </tr>
</table>

## 📜 Competitive Programming Template
To maintain high performance and code clarity, all competitive programming solutions in this repository utilize a **Triple-Layer Architecture**. This decouples I/O stream synchronization from the core algorithmic logic.

```cpp
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
```

## 🛠️ Implementation Deep-Dive

### 🌲 Trees & Advanced Data Structures

Our implementations focus on cache efficiency and generic usability.

* **[Segment Tree](./Implementations/Tree/Segment%20Tree/)**: Supports **vEB (van Emde Boas) layout** for better CPU cache locality. Level-aware combine logic allows for complex range queries.

> [!NOTE]
> **Performance Optimization (vEB Layout):**
> By arranging nodes in a van Emde Boas layout, this implementation significantly reduces CPU cache misses compared to the traditional $2i$ and $2i+1$ indexing. In large-scale benchmarks ($N > 10^5$), this results in a **10–30% speedup** for range queries.

* **[Splay Tree](./Implementations/Tree/Splay%20Tree/)**: A self-adjusting BST that moves frequently accessed nodes to the root.

### 🕸️ Graph Algorithms

* **Shortest Path**: `Dijkstra`, `Bellman-Ford`
* **MST**: `Prim's`, `Kruskal's`
* **Connectivity**: `Kosaraju` (SCC)


## 📊 Performance & Complexity

| Template | Build | Query | Space |
| --- | --- | --- | --- |
| **Segment Tree** | $O(n)$ | $O(\log n)$ | $O(n)$ |
| **Splay Tree** | $O(n \log n)$ | $O(\log n)^*$ | $O(n)$ |

<p align="left"><i>* Denotes amortized time complexity.</i></p>

---

## 🚀 Quick Start

### 1. Range Queries with Segment Tree
Our Segment Tree is highly flexible, allowing for custom combine logic and level-aware operations.

```cpp
// Example: Range Sum
std::vector<int> arr = {1, 2, 3, 4, 5};
SegmentTree<int> st(arr); 

int sum = st.query(1, 3); // Returns 9 (2 + 3 + 4)
st.update(2, 10);         // Update index 2 to value 10
```

### 2. Dynamic Sets with Splay Tree
The Splay Tree is ideal for scenarios where recently accessed elements need to be retrieved quickly.

```cpp
// Example: Self-adjusting BST
SplayTree tree = {10, 20, 30, 40};

tree.insert(25);      // Inserts 25 and splays it to the root
bool found = tree.contains(20); // Moves 20 to the root if found
tree.erase(30);       // Removes 30 and restructures optimally
```



