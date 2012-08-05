100\. A+B  
Hello, SGU

101\. Domino  
Eulerian path. Don't forget to judge if the graph is connected.

102\. Coprimes  
When N equals 1, the answer is 1.

103\. Traffic Lights  
There might be adjacent traffic lights whose colors always differ from
each other.

104\. Little shop of flowers  
Let $f[i][j]$ denote the maximum pleasant effect if the i-th flower is
put in vase j or the vases before it. Hence we have,
\\\[f[i][j] = \max\\\{f[i - 1][j - 1] + A[i][j], f[i][j - 1]\\\}\\\]

105\. Div 3  
1, 0, 0, 1, 0, 0, ...

106\. The equation  
Use the *%I64d* specifier to read or write *long long* integers. Damn
it.  
Check if all situations have been considered with small data (including
zeros).

        for (int a = -10; a <= 10; a++) {
            for (int b = -10; b <= 10; b++) {
                for (int c = -10;; c <= 10; c++) {
                    blahblah;
                    blahblah;
                    blahblah;
                }
            }
        }

107\. 987654321 problem  
Think about the case when N equals 9.

108\. Self-numbers 2  
Use a char as 8 bits to mark if a number is a self-number or not to fit
the memory limit.  
Not all items of s[1]...s[k] are different.

109\. Magic of David Copperfield II  
Parity counts.

110\. Dungeon  
The sequence of sphere numbers will be empty if the light ray hits none
of the spheres. In such a case, output nothing.

111\. Very simple problem  
It is a very simple problem indeed if you use *Java* and *BigInteger*.

112\. a^b-b^a  
Well. Java and BigInteger again....

113\. Nearly prime numbers  
$10^9 / 2 > \sqrt{10^9}$
