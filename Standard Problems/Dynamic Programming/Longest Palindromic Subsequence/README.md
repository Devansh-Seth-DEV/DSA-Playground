# Longest Palindromic Subsequence Solution

📝 **Given:**

We are given a finite sequence of characters:

$$
 \omega := \omega_1 \omega_2 \dots \omega_n \quad \text{ such that } \ \omega_i \in \lbrace a,b,\dots,z \rbrace \cup \lbrace \emptyset \rbrace , \quad \forall i \in \lbrace 1,2,\dots,n \rbrace
$$

From this sequence, we consider subsequences obtained by selecting **strictly increasing indices**. <br>
Formally, for an index subset

$$
S := \lbrace i_1,i_2,\dots,i_m \rbrace \subseteq \lbrace 1,2,\dots,n \rbrace ,  \quad i_1 < i_2 < \dots < i_m
$$

the subsequence is defined as

$$
\omega[S] := \omega_{i_1} \omega_{i_2} \dots \omega_{i_m}
$$

**Constraints:**

$$
1 \leq |\omega| \leq 1000
$$

where $|\omega|$ is the length of the input string.

<br>

🎯 **Objective:**

The goal is to determine the length of the longest palindromic subsequence in $\omega$,

A subsequence $u = \omega[S]$ is palindromic if

$$
u = \text{rev}(u)
$$

Formally:

$$
\text{Find:} \quad \max \big\lbrace |u| \mid u \subseteq \omega , \ u = \text{rev}(u) \big\rbrace
$$

<br>

# Brute Force Approach
> Note: For some inputs can give Time Limit Exceed Error


## 🔹Intermediate Functions

### $\pi(u)$ - Palindromic Validity Function
Checks if a subsequence is palindromic, and returns its length if valid.

$$
  \pi(u) :=
  \begin{cases}
  0, & u = \emptyset \ \lor \ u \neq \text{rev}(u) \\
  |u|, & u \neq \emptyset \ \land \ u = \text{rev}(u)
  \end{cases}
$$

### $\Psi^{(k)}$ - Extension of subsequence
Given a current subsequence $\Psi^{(k-1)}$ and a new character $\omega_k$, concatenating a new character at step $k$, defined as:

$$
\Psi^{(k)} := 
\begin{cases}
\omega_k, & \Psi^{(k-1)} = \emptyset \\
\Psi^{(k-1)}.\omega_k, & \Psi^{(k-1)} \neq \emptyset
\end{cases}
$$

$$
\forall k \in \lbrace 1,2,\dots,|w| \rbrace \quad \text{and} \quad \Psi^{(0)} := \emptyset
$$

where $\Psi^{(k-1)}$ is subsequence till $k-1$ steps.


## ⚡ $V^* \big(\Psi^{(k-1)}, k\big)$ - Optimal Value Function
Denote the optimal length of a palindromic subsequence obtainable from subsequence $\Psi$ when considering characters from position $k$ onward, defined as:

$$
V^* \big(\Psi^{(k-1)}, k\big) :=
\begin{cases}
0, & k = 0 \\
\pi\big(\Psi^{(k-1)}\big), & k > |\omega| \\
\max \bigg\lbrace \pi\big(\Psi^{(k-1)}\big), \ V^* \Big(\pi\big(\Psi^{(k)}\big), \ k+1\Big), \ V^* \Big(\pi\big(\Psi^{(k-1)}\big), \ k+1\Big) \bigg\rbrace, & \text{otherwise}
\end{cases}
$$

##

#### Final Problem

The original problem **“Longest Palindromic Subsequence”** is solved by computing:

$$ 
V^* \big(\Psi^{(0)}, 1\big)
$$

<br>

## Optimal Approach

### 💾 $\bar{V}(i, j)$ - Memoization Table
Let

$$
\bar{V}(i, j) := \text{ length of the longest palindromic subsequence in } \omega [i \dots j], \quad \text{for } \ 0 \leq i, j < |\omega| - 1
$$

### ✅ $\chi(i, j)$ - Indicator function
We define a boolean function $\chi(i, j)$ to track whether $\bar{V}(i, j)$ has already been computed:

$$
  \chi(i, j) := 
  \begin{cases}
  true,  & \bar{V} (i, j) \text{ is already computed} \\
  false, & \text{otherwise}
  \end{cases}
$$


## ⚡ $V^* (i, j)$ - Optimal Value Function
Representing the length of the longest palindromic subsequence in substring $\omega [i \dots j]$:

$$
V^* (i, j) :=
\begin{cases}
\bar{V}(i, j), & \chi(i, j) = true \\
0, & i > j \\
1, & i = j \\
2 + V^* (i+1, j-1), & \omega[i] = \omega[j] \\
\max\Big( V^* (i+1, j), \ V^* (i, j-1) \Big), & \text{otherwise}
\end{cases}
$$



##

#### Final Problem

The original problem **“Longest Palindromic Subsequence”** is solved by computing:

$$ 
V^* (0, |\omega|-1)
$$
