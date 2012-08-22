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
Good problem.  
Hint:
\\\[
f[i][s\_0] = \sum\_{k = 0}^{1 \dots 1}{f[i - 1][s\_k]}
\\\]
