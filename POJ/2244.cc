/*
 *  SRC: POJ 2244
 * PROB: Eeny Meeny Moo
 * ALGO: Math
 * DATE: Aug 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int m = 0;
        while (++m) {
            int res = 0;
            for (int i = 2; i < n; i++)
                res = (res + m) % i;
            if (!res) break;
        }
        printf("%d\n", m);
    }

    return 0;
}

