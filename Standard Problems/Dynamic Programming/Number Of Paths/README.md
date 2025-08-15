# Number Of Paths Solution

📝 **Given:**
- A grid of size $m \times n$
- Starting position: $(0, 0)$
- Ending position: $(m-1, n-1)$
- Allowed moves:
  - One step **right** $(x+1, y)$.
  - One step **down** $(x, y+1)$.

where:
  -  $1 \leq m,n \leq 100$

<br>

🎯 **Objective:**

The objective is to count the total number of unique paths from the start cell $(0, 0)$ to the end cell $(m-1, n-1)$, subject to the movement constraints.

Formally:

$$
\text{Find:} \quad \delta(0, 0)
$$

where $\delta(x, y)$ denotes the number of paths from $(x, y)$ to $(m-1, n-1)$.

##

### 🔹 $\Gamma(x, y)$ - Successor Function
The set of valid moves from $(x, y)$:

$$
  \Gamma(x, y) := \big\lbrace (x+1, y), (x, y+1) \big\rbrace \ \cap \ \lbrace 0,\dots,m-1 \rbrace \times \lbrace 0,\dots,n-1 \rbrace
$$

That is, from each cell we can only move **right** or **down**, provided we remain within the grid bounds.

<br>

### ⚡ $\delta(x, y)$ - State Transition Function / Step Function
The number of paths from $(x, y)$ is given by the recurrence:

$$
  \delta(x, y) :=
  \begin{cases}
  1, & (x, y) = (m-1, n-1) \\
  \\
  \\
  \\
  \displaystyle \sum_{p \in \Gamma(x, y)} \delta(p), & otherwise
  \end{cases}
$$

##

### 💾 $\bar{V}(x, y)$ - Memoization Vector 
To avoid recomputation, we store computed values:

$$
  \bar{V}(x, y) := \delta(x, y) \quad \text{once it has been evaluated}
$$

### ✅ $\chi(x, y)$ - Indicator function
We define a boolean function $\chi(x, y)$ to track whether $\bar{V}(x, y)$ has already been computed:

$$
  \chi(x, y) := 
  \begin{cases}
  true,  & \bar{V} (x, y) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$

##

#### Final Problem

The original problem "total number of unique paths in the grid" is solved by computing:

$$ 
  \delta(0, 0)
$$
