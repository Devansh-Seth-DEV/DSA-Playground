# Rod Cutting Solution

📝 **Given:**

- A rod of length $n \in ℤ^+$ inches
- A price table

$$
P := \lbrace P_1, P_2, \dots, P_n \rbrace
$$

where $P_i$ denotes the selling price of a rod piece of length $i$ inches.


**Constraints:**

$$
\begin{gather*}
1 \leq n \leq 1000 \\
1 \leq P_i \leq 10^6 \quad \forall i \in \lbrace 1,2,\dots,n \rbrace
\end{gather*}
$$

<br>

🎯 **Objective:**

The objective is to determine the **maximum revenue obtainable** by cutting a rod of length $n$ into one or more pieces (possibly zero), and selling each piece according to the given price table $P$.

Formally,

$$
\text{Find:} \quad \max \left\lbrace \sum^m\_{j=1} P_{l_j} \ \mid \ l_1 + l_2 + \dots + l_m = n, \ l_j \in ℤ^+ \right\rbrace
$$

<br>


## 🔹Intermediate Functions

### $\text{C}(i)$ - Cost Function
The immediate selling cost of a piece of length $i$ is defined as:

$$
\text{C}(i) := 
\begin{cases}
0, & i = 0 \\
P_i, & i>0
\end{cases}
$$

### 💾 $\bar{V}(i)$ - Memoization Table
We define a storage variable $\bar{V}(i)$ to represent the **maximum revenue obtainable** from a rod of length $i$ once computed

$$
\bar{V}(i) := V^* (i)
$$

### ✅ $\chi(i)$ - Indicator function
We define a boolean function $\chi(i)$ to track whether $\bar{V}(i)$ has already been computed:

$$
  \chi(i) := 
  \begin{cases}
  true,  & \bar{V} (i) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$


## ⚡ $V^* (i)$ - Optimal Value Function
Denote the **maximum revenue obtainable** from a rod of length $i$, defined as:

$$
V^* (i) :=
\begin{cases}
0, & i = 0 \\
\bar{V} (i), & \chi(i) = true \\
\max\limits_{k \in [1,n]} \left( \text{C}(k) + V^* (i-k) \right), & \text{otherwise}
\end{cases}
$$

where:
- $\text{C}(k)$ is the price of selling the first piece of length $k$.
- $V^* (i-k)$ is the maximum revenue obtainable from the remaining rod of length $i-k$.

##

#### Final Problem

The original problem **“Rod Cutting”** is solved by computing:

$$ 
V^* (n)
$$
