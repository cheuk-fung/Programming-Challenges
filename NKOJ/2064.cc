/*
 *  SRC: NKOJ 2064
 * PROB: GCC
 * ALGO: Math
 * DATE: Sep 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>

char buf[111];
int n, m;

long long calc(int n, int m)
{
    long long res = 1, fac = 1;
    for (int i = 1; i < n; i++) {
        fac = fac * i % m;
        res = (res + fac) % m;
    }

    return res % m;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%s%d", buf, &m);
        if (strlen(buf) >= log10(m)) printf("%lld\n", calc(m, m));
        else {
            n = 0;
            char *s = buf;
            while (*s) n = n * 10 + *s++ - '0';
            printf("%lld\n", calc(n + 1, m));
        }
    }

    return 0;
}
