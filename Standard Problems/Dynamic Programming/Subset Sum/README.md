# Subset Sum Solution

📝 **Given:**
- A set of integers $v=\lbrace v_1,v_2,\dots,v_n \rbrace$
- A target integer $T \geq 0$

where:
  -  $1 \leq n \leq 200$
  -  $1 \leq v_i \leq 200 \quad \forall i$
  -  $1 \leq T \leq 10^4$

<br>

🎯 **Objective:**

The objective is to decide whether there exists a subset of $v$ whose sum equals $T$

Formally:

$$
\text{Find:} \quad S \subseteq \lbrace 1,2,\dots,n \rbrace \quad \text{such that } \sum_{i \in S} v_i = T
$$

##

### ⚡ $F(i, T)$ - Feasibility function
It determines whether a subset of $\lbrace v_1,\dots,v_i \rbrace$ sums to $T$:

$$
  F(i, T) :=
  \begin{cases}
  true, & T = 0 \ \text{i.e} \ \ \exists S \subseteq \lbrace 1,\dots,i \rbrace \ | \sum_{k \in S} v_k = T\\
  false, & i = 0 \ \land \ T > 0 \\
  F(i-1, T), & T < v_i \\
  F(i-1, T) \ \lor \ F(i-1, T - v_i), & T \geq v_i
  \end{cases}
$$

##

### 💾 $\bar{V}(i, W)$ - Memoization Vector 
To avoid recomputation, we store computed values:

$$
  \bar{V}(i, W) := F(i, T) \quad \text{once it has been evaluated}
$$

### ✅ $\chi(i, W)$ - Indicator function
We define a boolean function $\chi(i, W)$ to track whether $\bar{V}(i, W)$ has already been computed:

$$
  \chi(i, W) := 
  \begin{cases}
  true,  & \bar{V} (i, W) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$

##

#### Final Problem

The original problem "Does there exist a subset of $v$ with sum equal to $T ?$" is solved by computing:

$$ 
  F(n, T)
$$
