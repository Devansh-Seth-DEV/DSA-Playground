# 0-1 Knapsack Solution

📝 **Given:**
- **$n$** be the number of items.
- **$W$** be the knapsack capacity.
- **$val[i]$** be the value of item $i$.
- **$wt[i]$** be the weight of item $i$.

<br>

🎯 **Objective:**

The objective is to maximize total value:

$$
\text{maximize } \sum_{i=1}^{n} val[i] x_i
$$

$$
\begin{aligned}
\text{such that: } &
\sum_{i=1}^{n} wt[i] x_i \le W, \quad x_i \in \lbrace 0, 1 \rbrace, \quad \forall i = 1,2,\dots,n
\end{aligned}
$$




##

### 🔹 $C(i,W)$ - Cost function 
The value contributed by item $i$, given capacity $W$:

$$
  C(i, W) :=
  \begin{cases}
  0, &  wt[i] > W \\
  val[i], & \text{otherwise}
  \end{cases}
$$

### 🔹 $W'(i, W)$ - Residual Capacity function 
The capacity left after considering item $i$:

$$
  W'(i, W) :=
  \begin{cases}
  W, &  wt[i] > W \\
  W - wt[i], & otherwise
  \end{cases}
$$


### ⚡ $V^* (i, W)$ - Optimal Value function 
The maximum value obtainable using the first $i$ items and capacity $W$:

$$
  V^* (i, W) :=
  \begin{cases}
  0, & i = 0 \text{ or } W = 0 \\
  \max\bigg(C(i, W) + V^* \Big(i-1, W'(i, W)\Big), \hspace{5pt} V^* (i, W) \bigg), & \text{otherwise}
  \end{cases}
$$

##

### 💾 $\bar{V}(i, W)$ - Memoization Vector 
To avoid recomputation, we store computed values:

$$
  \bar{V}(i, W) := V^* (i, W) \hspace{10pt} \text{once it has been evaluated}
$$

### 💡 $\chi(i, W)$ - Indicator function
We define a boolean function $\chi(i, W)$ to track whether $\bar{V}(i, W)$ has already been computed:

$$
  \chi(i, W) := 
  \begin{cases}
  true,  & \bar{V} (i, W) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$
