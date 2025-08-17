# Edit Distance Solution

📝 **Given:**

We are given two strings:

$$
s \in \Sigma^\*, \quad t \in \Sigma^\*
$$

where
- $\Sigma = \lbrace a,b,\dots,z \rbrace$ is the lowercase alphabet.
- $|s| = n$ is the length of string $s$.
- $|t| = m$ is the length of string $t$.


**Constraints:**

$$
1 \leq n,m \leq 1000
$$

<br>

🎯 **Objective:**

The goal is to compute the **minimum number of edit operations** required to transform string $s$ into string $t$.

The set of valid edit operations is defined as:
1. **Insertion** – insert a letter from $\Sigma$ into $s$.
2. **Deletion** – delete a letter from $s$.
3. **Replacement** – replace one letter of $s$ with another letter from $\Sigma$.

Formally,

$$
\text{Find:} \quad \min \Big\lbrace k \in ℕ \mid \exists \omega_0, \dots, \omega_k \in \Sigma^\* \ : \ \omega_0 = s, \ \omega_k = t, \ \omega_i \sim \omega_{i-1}, \ \forall i \in [1,k] \Big\rbrace
$$

<br>


## 🔹Intermediate Functions

### 💾 $\bar{V}(i,j)$ - Memoization Table
Represents the minimum number of operations required to convert the suffix of $s$ starting at position $i$ into the suffix of $t$ starting at position $j$, once computed:

$$
\bar{V}(i,j) := V^* (i,j) 
$$

### ✅ $\chi(i,j)$ - Indicator Function
We define a boolean function $\chi(i,j)$ to track whether $\bar{V}(i,j)$ has already been computed:

$$
  \chi(i,j) := 
  \begin{cases}
  true,  & \bar{V} (i,j) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$


## ⚡ $V^* (i,j)$ - Optimal Value Function
Denotes the **minimum number of edit operations** needed to convert string $s$ of length $n$, into $t$ of length $m$.

Defined as:

$$
V^* (i,j) :=
\begin{cases}
m-j+1, & i>n \ \ (\text{all remaining characters of} t \text{must be inserted}) \\
n-i+1, & j>m \ \ (\text{all remaining characters of} s \text{must be deleted}) \\
\bar{V}(i,j), & \chi(i,j) = true \\
V^* (i+1, j+1), & s[i] = t[j] \\
1 + \min \Big\lbrace V^* (i,j+1), V^* (i+1,j), V^*(i+1,j+1) \Big\rbrace, & \text{otherwise}
\end{cases}
$$

where:
- $V^* (i,j+1)$: corresponds to **insertion** of $t[j]$.
- $V^* (i+1,j)$: corresponds to **deletion** of $s[i]$.
- $V^* (i+1,j+1)$: corresponds to **replacement** of $s[i]$ by $t[j]$.

##

#### Final Problem

The original problem **“Edit Distance”** is solved by computing:

$$ 
V^* (1,1)
$$
