# 📝 Maximum Subarray Sum with Range Query and Point Update

## 📄 Problem Description
Given an integer array `arr` of size `n`, support two types of operations efficiently:

- **Range Query:** For a given range `[l, r]`, find the maximum subarray sum that lies entirely within that range. The subarray can be empty (i.e., sum = 0).
- **Point Update:** Update the value at index `i` to a new value `val`.

The solution supports:
- Negative numbers
- Dynamic updates
- Empty subarray (i.e., sum = 0 when all elements are negative)

### 🛠 Approach
Uses a segment tree where each node stores:
- `sum`: Total sum of the segment
- `pref`: Maximum prefix sum
- `suff`: Maximum suffix sum
- `maxsum`: Maximum subarray sum in the segment

### Constraints

- $1 ≤ N ≤ 10^5$
- $1 ≤ Q ≤ 10^5$
- $0 ≤ i < N$
- $-10^5 ≤ a[i], val ≤ 10^5$
- $0 ≤ l ≤ r < N$

### Limits

- `Time Limit: 1 second (cpp)`
- `Memory Limit: 256 MB`

### Input Format

```txt
N Q
a[0] a[1] ... a[N-1]
Q operations of the form:
  1 l r     → Query maximum subarray sum in range [l, r]
  2 i val   → Update a[i] = val
```

---

## 🧪 Sample Test Cases

### Test Case: 1
#### Input:

```txt
6 4
-5 2 3 -1 2 -10
1 0 5
2 0 10
1 0 5
1 2 4
```

#### Output:
```txt
6
16
4
```

#### Explanation:
- `1 0 5`   → Max subarray in [-5, 2, 3, -1, 2, -10] is [2, 3, -1, 2] = 6
- `2 0 10`  → arr becomes [10, 2, 3, -1, 2, -10]
- `1 0 5`   → Max subarray is now [10, 2, 3, -1, 2] = 16
- `1 2 4`   → Max subarray in [3, -1, 2] = 4

<br>

### Test Case: 2
#### Input:

```txt
5 3
-1 -2 -3 -4 -5
1 0 4
2 2 10
1 1 3
```

#### Output:
```txt
0
10
```

#### Explanation:
- Initially all elements negative → max subarray is empty → 0
- Update `a[2] = 10` → arr = [-1, -2, 10, -4, -5]
- New query on `[1, 3]` → best subarray = [10] → 10

<br>

### Test Case: 3
#### Input:

```txt
4 3
1 -2 3 -1
1 0 3
2 1 5
1 0 3
```

#### Output:
```txt
3
9
```

#### Explanation:
- Query on `[0, 3]` → best subarray = [3]
- Update `a[1] = 5` → arr = [1, 5, 3, -1]
- New max subarray in `[0, 3]` = [1, 5, 3] = 9
