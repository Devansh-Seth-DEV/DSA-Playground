# Longest Common Subsequence Solution

📝 **Given:**
- Two strings $\omega_1, \omega_2 \in \Sigma^\*$, where $\Sigma^\* \in \lbrace A,B,\dots,Z \rbrace \cup \lbrace \emptyset \rbrace$
- $|\omega_1| = n, \ |\omega_2| = m$
- $\omega_1[i]$ denotes $i^{th}$ character of string $\omega_1$, with $i \in \lbrace 1,2,\dots,n \rbrace$.
- $\omega_2[j]$ denotes $j^{th}$ character of string $\omega_2$, with $j \in \lbrace 1,2,\dots,m \rbrace$.

where:
  -  $1 \leq n,m \leq 10^3$

<br>

🎯 **Objective:**

Find the length of the **longest subsequence** common to both $\omega_1$ and $\omega_2$

Formally:

$$
\text{Find:} \quad \max \Big\lbrace |S| \ | \ S \text{ is a subsequence of both } \omega_1 \text{ and } \omega_2 \Big\rbrace
$$

##

### ⚡ $V^* (i, j)$ - Optimal Value Function
The length of the longest common subsequence between prefixes $\omega_1[1 \dots i]$ and $\omega_2[1 \dots j]$:

$$
  V^* (i, j) :=
  \begin{cases}
  0, & i \notin \lbrace 1,2,\dots,n \rbrace \ \lor \ j \notin \lbrace 1,2,\dots,m \rbrace \\
  1 + V^* (i-1, j-1), & \omega_1[i] = \omega_2[j] \\
  \max \Big( V^* (i-1, j), \ V^*(i, j-1) \Big), & \text{otherwise}
  \end{cases}
$$

##

### 💾 $\bar{V}(i, j)$ - Memoization Vector 
To avoid recomputation, we store computed values:

$$
  \bar{V}(i, j) := V^* (i, j) \quad \text{once it has been evaluated}
$$

### ✅ $\chi(i, j)$ - Indicator function
We define a boolean function $\chi(i, j)$ to track whether $\bar{V}(i, j)$ has already been computed:

$$
  \chi(i, j) := 
  \begin{cases}
  true,  & \bar{V}(i, j) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$

##

#### Final Problem

The original problem "length of the longest common subsequence" is solved by computing:

$$ 
  V^* (n, m)
$$
