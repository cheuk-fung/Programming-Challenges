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

TODO: 121\. Bridges painting  
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

124\. Broken line  
I didn't mention that all segments are parallel to coordinate axes until
I got an AC, which led me to write a generic but a bit complex
algorithm....  

1. Sort all segment endpoints in clockwise or anticlockwise order to
   form a *cycle*. Actually, I found an Eulerian path among these
   points.
2. If the point belongs to the broken line, return "BORDER".
3. If the absolute value of the sum of angles of the given point and
   every two consecutive endpoints in the sorted cycle (angles maybe
   either positive or *negtive*) equals $2\pi$, return "INSIDE",
   otherwise "OUTSIDE".

125\. Shtirlits  
Enumerate A[i][j] one by one with a brute force DFS and check if each
A[i][j] whose neighbors are all assigned satisfies B[i][j] at every
step.

TODO: 126\. Boxes  
Failed to solve a number theory problem *again*.

127\. Telephone directory  
Sort and count.
