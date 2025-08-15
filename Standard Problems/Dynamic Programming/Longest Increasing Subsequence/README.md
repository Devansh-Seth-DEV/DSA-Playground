# Longest Increasing Subsequence Solution

📝 **Given:**
- A set of integers $v=\lbrace v_0,v_1,\dots,v_{N-1} \rbrace$

where:
  -  $1 \leq N \leq 10^3$
  -  $0 \leq v_i \leq 10^6 \quad \forall i$

<br>

🎯 **Objective:**

The objective is to find the length of the longest subsequence of $v$ that is **strictly increasing**.

Formally:

$$
\text{Find:} \quad \max \big\lbrace |S| : \ 0 \leq i_1 < i_2 < \dots < i_k < N, \ v_{i_1} < v_{i_2} < \dots < v_{i_k} \big\rbrace
$$

##

### ⚡ $V^* (i, T)$ - Optimal Value Function
The maximum achievable length of an increasing subsequence using elements from indices $[i, N-1]$, given that the last chosen index is $T$ (where $T = -1$ denotes “no element chosen yet”).

Formally:

$$
  V^* (i, T) :=
  \begin{cases}
  0, & i \geq N \\
  \max\Big(1 + V^* (i+1, i), \ V^* (i+1, T) \Big), & T = -1 \ \lor \ v_T < v_i \\
  V^* (i+1, T), & otherwise
  \end{cases}
$$

##

### 💾 $\bar{V}(i, T)$ - Memoization Vector 
To avoid recomputation, we store computed values:

$$
  \bar{V}(i, T) := V^* (i, T) \quad \text{once it has been evaluated}
$$

### ✅ $\chi(i, T)$ - Indicator function
We define a boolean function $\chi(i, T)$ to track whether $\bar{V}(i, T)$ has already been computed:

$$
  \chi(i, T) := 
  \begin{cases}
  true,  & \bar{V} (i, T) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$

##

#### Final Problem

The original problem "length of the Longest Increasing Subsequence" is solved by computing:

$$ 
  V^* (0, -1)
$$
