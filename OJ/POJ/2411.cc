/*
 *  SRC: POJ 2411
 * PROB: Mondriaan's Dream
 * ALGO: DP
 * DATE: Jul 17, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, m;
long long f[2][1 << 11];
long long* curr;
long long* next;
int full;

void solve(int orig, int _curr, int _next)
{
    if (_curr + 1 == full) {
        next[_next] += curr[orig];

        return ;
    }

    for (int i = 0; i < m; i++) {
        int del = 1 << i;
        if ((_curr & del) == 0) {
            if ((_next & del) == 0)
                solve(orig, _curr | del, _next | del);
            if (i + 1 < m && (_curr & (del << 1)) == 0)
                solve(orig, _curr | del | (del << 1), _next);

            return ;
        }
    }
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!(n || m)) break;

        if (n * m % 2) {
            puts("0");
            continue ;
        }

        memset(f, 0, sizeof(f));

        curr = f[0];
        next = f[1];

        curr[0] = 1;

        full = 1 << m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < full; j++)
                solve(j, j, 0);

            long long* tmp = curr;
            curr = next;
            next = tmp;

            memset(next, 0, sizeof(f[0]));
        }

        printf("%lld\n", curr[0]);
    }

    return 0;
}
