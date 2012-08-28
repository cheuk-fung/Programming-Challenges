130\. Circle  
No two of the chords can intersect if the circle is broken into minimal
possible amount of parts. We can connect A<sub>1</sub> to A<sub>2</sub>,
A<sub>4</sub>, ... , or A<sub>2k</sub>, which divides the circle into
two parts. Then we treat each part as a new "circle" and count different
ways by recursion and combinations. That's,
\\\[
F(k) = \begin{cases}
0,                                               & k = 0 \\\\
\sum\_{i = 0}^{k - 1}{F(i) \times F(k - 1 - i)}, & k > 0
\end{cases}
\\\]
Actually, we don't need any recursion. DP based on this formula is
better.

131\. Hardwood floor  
Good problem. We can solve it with DP and bitwise operations.  
Let $s\_{i}$ denote the states of row i. If the j-th column of row i is
covered, the j-th bit of $s\_{i}$ will be 1, otherwise 0.  
Let $(s, s')$ denote the states of two adjacent rows and
$s\_{i} \to s\_{i + 1}$ denote that we can cover row i and row i + 1
starting from $(s\_{i}, 0)$ to $(1 \dots 1, s\_{i + 1})$ using DFS.  
Then we have,
\\\[
f[i + 1][s\_{i + 1}] = \sum\_{s\_{i} \to s\_{i + 1}}{f[i][s\_{i}]}
\\\]
Since the row beyond the last row cannot be covered, the answer is
$f[m + 1][0]$.

132\. Another Chocolate Maniac  
Similar to the previous problem. Note that the matrix is _M * N_ not _N
* M_.  
Let $is\_{i}$ denote the initial state of row i. If the j-th column of
the row is '\*', the j-th bit of $is\_{i}$ will be 1, otherwise 0.  
Let $(s\_{i - 1}, s\_{i}) \to (s\_{i}', s\_{i + 1})$ denote covering
from $(s\_{i - 1}, s\_{i}, is\_{i + 1})$ to
$(s\_{i - 1}, s\_{i}', s\_{i + 1})$ where no other piece may be placed
on row i with state $s\_{i}'$. We need $cnt$ more pieces of chocolate to
achieve this.  
Then we have,
\\\[
f[i + 1][s\_{i + 1}][s\_{i}'] = \min\_{(s\_{i - 1}, s\_{i}) \to (s\_{i}', s\_{i + 1})}{f[i][s\_{i}][s\_{i - 1}] + cnt}
\\\]
The answer is $\min\_{s\_{m} = 0}^{1 \dots 1}{f[m + 1][0][s\_{m}]}$.
What's more, use `int` for array `f[71][1 << 7][1 << 7]` will exceed the
memory limit but `short int` is fine.

133\. Border  
Sort and count.

134\. Centroid  
Arbitrarily choose a vertex as root and then traverse the tree by DFS to
get the size of every sub-tree.  
Let $(u, v)$ denote a *directed* edge in the tree and $\mathbb{E}$
denote the set of all such edges. The associated value of vertex u is:
\\\[
\max\\{\max\_{(u, v) \in \mathbb{E}}{size[v]}, N - size[u]\\}
\\\]
