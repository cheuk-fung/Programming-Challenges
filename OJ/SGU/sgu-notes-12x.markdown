120\. Archipelago  
Find the center $(x\_c, y\_c)$ of the N-gon using the two given points.
Then we can calculate the next point $(x', y')$ counterclockwise based
on $(x, y)$:
\\\[
\theta = \frac{2\pi}{n},\quad
\begin{bmatrix} x' \\\\ y' \end{bmatrix} =
\begin{bmatrix}
\cos\theta & -\sin\theta \\\\
\sin\theta & \cos\theta
\end{bmatrix}
\begin{bmatrix} x - x\_c \\\\ y - y\_c \end{bmatrix} +
\begin{bmatrix}x\_c \\\\ y\_c \end{bmatrix}
\\\]
Add an offset(e.g. 1e-12) to a floating number to avoid outputting
**-0.000000**.

121\. Bridges painting  
Don't know how to solve it yet :(

122\. The book  
Find a Hamiltonian path. According to
[Ore's theorem](https://en.wikipedia.org/wiki/Ore%27s_theorem), the
given graph must be Hamiltonian. Thus the problem can be solved by
[this](https://en.wikipedia.org/wiki/Ore%27s_theorem#Algorithm) simple
but beautiful algorithm.  
Trick: If $i + 1 > j$, reversing the part of the cycle between
$v\_{j + 1}$ and $v\_i$ (inclusive) is equivalent but much more
convenient.

123\. The sum  
I found [WolframAlpha](http://www.wolframalpha.com/) is fun :) I typed
"sum of fibonacci 1 to 41" then it returned
$\sum\_{n = 1}^{40}F\_n = 267914295$ to me. Hence I knew that an *int*
is enough to represent the answer.
