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
    static int process(int n) {
        int result = 0;
        
        // --- Implementation Logic Start ---
        
        // --- Implementation Logic End ---
        
        return result;
    }
};

int main() {
    fastIO();
    Solver::execute();
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


