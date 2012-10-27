/*
 *  SRC: ZOJ 3520
 * PROB: Hello, Gensokyo 
 * ALGO: NULL
 * DATE: Oct 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

long long f[100001];

int main()
{
    f[1] = 0;
    for (int i = 2, addition = 1; i < 100001; i++) {
        f[i] = f[i - 1] + addition;
        if (i & 1) addition++;
    }

    int n;
    while (~scanf("%d", &n)) {
        printf("%lld\n", f[n]);
    }

    return 0;
}

