/*
 *  SRC: NKOJ 1221
 * PROB: Recaman's Sequence
 * ALGO: NULL
 * DATE: Aug 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAX_N = 500001;

int f[MAX_N];
bool vis[3000000];

int main()
{
    for (int i = 1; i < MAX_N; i++) {
        f[i] = f[i - 1] - i;
        if (f[i] <= 0 || vis[f[i]]) f[i] += i + i;
        vis[f[i]] = 1;
    }

    int k;
    while (scanf("%d", &k), k != -1) printf("%d\n", f[k]);

    return 0;
}
