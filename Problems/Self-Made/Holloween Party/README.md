# 🎃 Holloween Party

![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for)

![Technique: 0–1 BFS](https://img.shields.io/badge/0–1%20BFS-blue?style=for)
![Technique: Dijkstra](https://img.shields.io/badge/Dijkstra-blue?style=for)
![Concept: Shortest Path](https://img.shields.io/badge/Shortest%20Path-yellow?style=for)
![Category: Grid Path](https://img.shields.io/badge/Grid%20Path-lightgrey?style=for)
![Graph: Implicit](https://img.shields.io/badge/Graph-Implicit-brightgreen?style=for)

<br>

## 📝 Problem Description

Festive season is going on in the city of **Kam kaj nai**. Though most of the people in the city of **kam kaj nai** aren’t serious about their work and their main motivation of living is do a party in every day. **Torongo** being most sincere person in the city of **kam kaj nai** never wants to take day off for this unnecessary parties. But he is also very kind never wants to hard anyone of the city of **kam kaj nai**.

**Torongo’s** house located at cell `(0, 0)` in the gird wise representation of city of **kam kaj nai** and his office located at cell `(n–1, m–1)`. Inorder to go on cell to another cell torongo needs to visit one of 4 adjacent cell ( Right , Left , Up , Down ) from is current cell.

Today people of the city **kam kaj nai** celebrating **Holloween party** in their house so there is a dress code to attain the party . If currently torongo at `(x1, y1)` position and his next destination is `(x2, y2)` position then
- If `DressCode(x1, y1) == DressCode(x2, y2)` torongo **can go** to `(x2, y2)` position without changing his dress.
- If `DressCode(x1, y1) != DressCode(x2, y2)` torongo **can’t go** to `(x2, y2)` position without changing his dress.
  
Find the **minimum number of dress changes** required to go from his **home (0, 0)** to his **office (n-1, m-1)**.

## Constraints
- $1 ≤ t ≤ 15$
- $1 ≤ n, m ≤ 1000$
- $1 ≤ DressCode(x, y) ≤ 9$

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
Where `X` is the test case number and `Y` is the **minimum number of dress changes** required.

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
