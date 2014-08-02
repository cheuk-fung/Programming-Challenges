110\. Dungeon  
Find the sphere the light hits first and calculate its reflected ray
again and again until no sphere will be hit.  
The sequence of sphere numbers will be empty if the light ray hits none
of the spheres. In such a case, output nothing.

111\. Very simple problem  
It is a very simple problem indeed if you use *Java* and *BigInteger*.

112\. a^b-b^a  
Well. Java and BigInteger again....

113\. Nearly prime numbers  
$10^9 / 2 > \sqrt{10^9}$

114\. Telecasting station  
It has multiple acceptable answers and is special judged, which is not
mentioned by the problem statement. One of these acceptable points for
station is always locates in one of these cities.

115\. Calendar  

    #include <ctime>

116\. Index of super-prime  
Viewing the input number as a knapsack and super-prime numbers as items,
the problem actually is an unbounded knapsack problem. Hence we can
solve it with a dp algorithm.  
But, well, a brute-force search is also acceptable.

117\. Counting  
Count the number of each prime factor of K and compared with that of
each number.

118\. Digital Root  
If $9 \mid n$ then $f(n) = n \bmod{9}$ else $f(n) = 9$. And it's easy to
prove that $f(m + n) = f(f(m) + f(n))$ and
$f(m \times n) = f(f(m) \times f(n))$.

119\. Magic Pairs  
\\\[
\forall x, y \in \mathbb{Z},\ 
\text{if } N \mid A\_0x + B\_0y,\ \text{then } N \mid Ax + By \iff
\begin{cases}
A \equiv A\_0k \pmod{N} \\\\
B \equiv B\_0k \pmod{N}
\end{cases}
, 0 \le k < N
\\\]
