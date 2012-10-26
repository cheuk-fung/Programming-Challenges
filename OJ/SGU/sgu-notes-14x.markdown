140\. Integer Sequences  
\\\[
A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_n * X\_n \equiv B \pmod{P}
\Rightarrow \exists x,y \in \mathbb{Z},\ (A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_n * X\_n) * x + P * y = B
\\\]

It doesn't matter if we let
$X\_1 = X\_1 * x, X\_2 = X\_2 * x, \ldots, X\_n = X\_n * x$. Thus we
have,
\\\[
A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_n * X\_n + P * y = B
\Rightarrow B \mid gcd(A\_1, A\_2, \ldots, A\_n, P)
\\\]

So now we need to solve
\\\[
A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_n * X\_n + P * y = gcd(A\_1, A\_2, \ldots, A\_n, P)
\\\]

My solution translates this equation to
\\\[
A\_n * x + (A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_{n - 1} * X\_{n - 1} + P * y') * y = gcd(A\_n, gcd(A\_1, A\_2, \ldots, A\_{n - 1}, P))
\\\]

Then uses **extended Euclidean algorithm** to solve out $x$ and $y$. After
that we can get the *minimum* $X\_n$ and corresponding $y''$. Therefore
the problem now is
\\\[
A\_{n - 1} * x + (A\_1 * X\_1 + A\_2 * X\_2 + \cdots + A\_{n - 2} * X\_{n - 2} + P * y') * y = gcd(A\_{n - 1}, gcd(A\_1, A\_2, \ldots, A\_{n - 2}, P))
\\\]

Solve it by the same way and multiply the answer by $y''$ we got before
then get the minimum $X\_{n - 1}$.  
Step by step, we can get all the elements of $\mathbf{X}$.
