/*
 *  SRC: POJ 2287
 * PROB: Tian Ji -- The Horse Racing
 * ALGO: Greedy + DP
 * DATE: Jul 18, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

int n;
int a[1010], b[1010], f[1010][1010];

int greater(int a, int b)
{
    return a > b;
}

inline int max(int a, int b)
{
    return a > b ? a : b;
}

inline int judge(int i, int j)
{
    if (a[i] > b[j]) return 200;
    if (a[i] < b[j]) return -200;
    return 0;
}

int main()
{
   while (scanf("%d", &n) != EOF) {
       if (n == 0) break;

       for (int i = 1; i <= n; i++)
           scanf("%d", a + i);
       for (int i = 1; i <= n; i++)
           scanf("%d", b + i);

       sort(a + 1, a + n + 1, greater);
       sort(b + 1, b + n + 1, greater);

       f[0][0] = 0;
       for (int i = 1; i <= n; i++) {
           f[i][0] = f[i - 1][0] + judge(n - i + 1, i);
           for (int j = 1; j < i; j++)
               f[i][j] = max(f[i - 1][j - 1] + judge(j, i), f[i - 1][j] + judge(n - (i - j) + 1, j));
           f[i][i] = f[i - 1][i - 1] + judge(i, i);
       }

       int ans = -0x3FFFFFF;
       for (int i = 0; i <= n; i++)
           ans = max(ans, f[n][i]);

       printf("%d\n", ans);
   } 

   return 0;
}
