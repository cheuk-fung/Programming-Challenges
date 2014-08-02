/*
 *  SRC: NKOJ 1131
 * PROB: 编辑距离问题
 * ALGO: DP
 * DATE: Aug 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

char a[2012], b[2012];
int f[2][2012];
int* curr = f[0];
int* prev = f[1];

inline int min(int a, int b) { return a < b ? a : b; }

int main()
{
    while (scanf("%s%s", a, b) == 2) {
        int n = strlen(a), m = strlen(b);
        for (int i = 1; i <= m; i++) prev[i] = i;
        for (int i = 1; i <= n; i++) {
            curr[0] = i;
            for (int j = 1; j <= m; j++) {
                if (a[i - 1] == b[j - 1]) curr[j] = prev[j - 1];
                else curr[j] = min(curr[j - 1], min(prev[j - 1], prev[j])) + 1;
            }
            int* t = curr;
            curr = prev;
            prev = t;
        }
        printf("%d\n", prev[m]);
    }

    return 0;
}
