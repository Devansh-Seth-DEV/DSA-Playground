# 🎃 Holloween Party

![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-red?style=for)

![Technique: 0–1 BFS](https://img.shields.io/badge/0–1%20BFS-blue?style=for)
![Technique: Dijkstra](https://img.shields.io/badge/Dijkstra-blue?style=for)
![Concept: Shortest Path](https://img.shields.io/badge/Shortest%20Path-yellow?style=for)
![Category: Grid Path](https://img.shields.io/badge/Grid%20Path-lightgrey?style=for)
![Graph: Implicit](https://img.shields.io/badge/Graph-Implicit-brightgreen?style=for)

<br>

## 📝 Problem Description

In the city of **“Kam Kaj Nai”**, people love partying daily, especially on Halloween. **Torongo**, the only sincere citizen, lives at cell `(0, 0)` and works in office at cell `(n–1, m–1)` in a rectangular grid city.

Each cell has a dress code (represented as a character), and Torongo can move to adjacent cells in 4 directions: up, down, left, right.

He can move:
- **Freely** to a neighboring cell with the same dress code
- **Only after changing clothes** if the neighboring cell has a different dress code

Find the **minimum number of dress changes** required to go from his **home (0, 0)** to his **office (n-1, m-1)**.

## Constraints
- $1 ≤ t ≤ 15$
- $1 ≤ n, m ≤ 1000$

## Limits
- `Time Limit: 2 seconds (cpp)`
- `Memory Limit: 512 MB`
  

## 📥 Input Format

```txt
t                      // Number of test cases
n m                    // Grid dimensions
grid[0]
grid[1]
...
grid[n-1]
```

## 📤 Output Format
```txt
Case X: Y
```

---

## 🧪 Sample Test Cases

### Test Case: 1

#### Input
```txt
2
2 2
11
11
2 3
123
456
```


#### Output
```txt
Case 1: 0
Case 2: 3
```
