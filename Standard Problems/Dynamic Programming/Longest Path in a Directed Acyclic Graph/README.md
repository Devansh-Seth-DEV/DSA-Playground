# Longest Path in a Directed Acyclic Graph Solution

📝 **Given:**
- A directed weighted graph $G = (V, E, w)$
- A source vertex $s \in V$

where:
  -  $V \subseteq ℤ^+ \ \cup \ \lbrace 0 \rbrace$, the set of vertices.
  -  $|V| = n$, the number of vertices.
  -  $E \subseteq V \times V$, the set of directed edges.
  -  $|E| = m$, the number of directed edges.
  -  $w = E \to ℤ$, weight function assigning integer weights to edges.

**Constraints:**

$$
\begin{gather*}
1 \leq n \leq 10^3 \\
\\
1 \leq m \leq \frac{n(n-1)}{2} \\
\\
0 \leq E(i,0), \ E(i,1) < n \\
\\
-100 \leq w(e) \leq 100, \quad \forall e \in E
\end{gather*}
$$


<br>

🎯 **Objective:**

For a given source vertex $s \in V$, compute the longest distance from $s$ to all other vertices $v \in V$.

Formally:

$$
\text{Find:} \quad \Big( d^{\max}_s (v) \Big) _{v \in V} \quad \text{where} \ d^{\max}_s (v) \ \text{denotes the maximum path distance from} \ s \text{ to } v
$$

<br>

# Brute Force Approach
> Note: Give Time Limit Exceed Error


## 🔹Intermediate Functions

### $\alpha_{u,v}$ - Adjacency Pair

$$
  \alpha_{u,v} := \Big(v, \ w(u,v) \Big) \quad \forall (u,v) \in E
$$

### $\Gamma^+_G (u)$ - Directed Neighbour Function
The out-neighbourhood of $u$:

$$
\Gamma^+\_G(u) := \big \lbrace \alpha_{u,v} \mid v \in V, (u,v) \in E \big \rbrace
$$

### $\text{Reach}_G (u)$ - Reachability Function
The set of all vertices reachable from $u$:

$$
\text{Reach}\_G (u) := \big \lbrace v \in V \mid \exists \text{ a path from } u \to v \big \rbrace
$$

Equivalently:

$$
\text{Reach}\_G (u) := \lbrace u \rbrace \cup \bigcup_{x \in \Gamma^+\_G (u)} \text{Reach}\_G (x)
$$

### $\Pi^{\max}\_{u \to v}$ Maximum Path Function
The length of the maximum-weight path from $u$ to $v$:

$$
\Pi^{\max}\_{u \to v} := 
\begin{cases}
\max \big\lbrace (p, \ l(p)) \mid p \text{ is a path from } u \text{ to } v \big\rbrace, & v \in \text{Reach}\_G (u) \\
-\infty, & \text{otherwise}
\end{cases}
$$

where

$$
l(p) := \sum_{e \in p} w(e)
$$

### $d^{\max}\_G (u,v)$ - Maximum Path Distance function
The maximum distance from vertex $u$ to $v$:

$$
d^{\max}\_G (u, v) := 
\begin{cases}
l(p), & p \in \Pi^{\max}\_{u \to v} \ \land \ v \in \text{Reach}\_G (u) \\
-\infty, & v \notin \text{Reach}\_G (u)
\end{cases}
$$

## ⚡ $V^* (u)$ - Optimal Value Function
A Vector containing the longest path distance from source $u$ to every vertex $v \in V$:

$$
  V^* (u) := \Big( d^{\max}\_G (u, v) \Big)\_{v \in V}
$$

##

#### Final Problem

The original problem "longest path distances in a DAG from a source vertex $s$" is solved by computing:

$$ 
  V^* (s)
$$

<br>

## Optimal Approach

## 🔹Intermediate Functions

### $\alpha_{u,v}$ - Adjacency Pair

$$
  \alpha_{u,v} := \Big(v, \ w(u,v) \Big) \quad \forall (u,v) \in E
$$

### $\Gamma^+_G (u)$ - Directed Neighbour Function
The out-neighbourhood of $u$:

$$
\Gamma^+\_G(u) := \big \lbrace \alpha_{u,v} \mid v \in V, (u,v) \in E \big \rbrace
$$

### $\delta(u)$ - DFS Traversal Function
Used to compute a topological ordering of vertices.

$$
\delta(u) :=
\begin{cases}
\emptyset, & u \in \text{visited} \\
\text{push } u \text{ after } \delta(v), & \forall v \in \Gamma^+\_G (u) 
\end{cases}
$$

### $\tau^{-1}\_G (u)$ - Topological Ordering Function
Maps positions to vertices, $\tau\_G$ is bijective i.e every vertiex gets unique position and all positions are used

$$
\tau^{-1}\_G := \lbrace 1,2,\dots,n \rbrace \longleftrightarrow V \quad
\text{such that } \forall (u,v) \in E, \ \tau^{-1}\_G (u) < \tau^{-1}\_G (v)
$$

## ⚡ $V^* (u)$ - Optimal Value Function
A Vector containing the longest path distance from source $u$ to every vertex $v \in V$:

$$
  V^* (u) := \Big( \text{dist}^{(n)}\_u (v) \Big)\_{v \in V}
$$

where $\text{dist}^{(k)}\_u (v)$ is updated in **topological order** as:

$$
\text{dist}^{(0)}\_u (v) :=
\begin{cases}
0, & v = u \\
-\infty, & v \neq u
\end{cases}
$$

$$
\text{dist}^{(k)}\_u (z) :=
\begin{cases}
\max \Big( \text{dist}^{(k-1)}\_u (z), \ \text{dist}^{(k-1)}\_u (v_k) + w(v_k, z) \Big), & z \in \Gamma^+\_G (v_k) \\
\text{dist}^{(k-1)}\_u (z), & \text{otherwise}
\end{cases}
$$

where:
- For each $k = 1,2,\dots,n$
- $v_k = \tau^{-1}\_G (k)$ is the $k$-th vertex in topological order.
- $\text{dist}^{(k-1)}\_u (z)$ is distance vector before updating vertex $v_k$ (after $k-1$ iterations).
- $\text{dist}^{(k)}\_u (z)$ is distance vector after processing $v_k$ (after $k$ iterations).

##

#### Final Problem

The original problem "longest path distances in a DAG from a source vertex $s$" is solved by computing:

$$ 
  V^* (s)
$$
