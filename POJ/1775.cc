/*
 *  SRC: POJ 1775
 * PROB: Sum of Factorials
 * ALGO: NULL
 * DATE: Aug 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int fac[10];

int main()
{
    fac[0] = 1;
    for (int i = 1; i < 10; i++) fac[i] = fac[i - 1] * i;
    int n;
    while (scanf("%d", &n), n >= 0) {
        if (n == 0) puts("NO");
        else {
            for (int i = 9; i >= 0 && n; i--)
                if (n >= fac[i]) n -= fac[i];
            puts(n ? "NO" : "YES");
        }
    }
    
    return 0;
}

