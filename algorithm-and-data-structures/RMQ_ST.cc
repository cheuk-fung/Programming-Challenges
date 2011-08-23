/*
 *  SRC: POJ 3264
 * PROB: Balanced Lineup
 * ALGO: RMQ_ST
 * DATE: Jul 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

inline int max(int a, int b)
{
    return a > b ? a : b;
}

inline int min(int a, int b)
{
    return a < b ? a : b;
}

int max_v[20][50010], min_v[20][50010];

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &max_v[0][i]);
        min_v[0][i] = max_v[0][i];
    }

    for (int i = 1; 1 << i <= n; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            max_v[i][j] = max(max_v[i - 1][j], max_v[i - 1][j + (1 << (i - 1))]);
            min_v[i][j] = min(min_v[i - 1][j], min_v[i - 1][j + (1 << (i - 1))]);
        }

    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int pos = log(r - l + 1.0) / log(2.0);
        printf("%d\n", max(max_v[pos][l], max_v[pos][r - (1 << pos) + 1]) - min(min_v[pos][l], min_v[pos][r - (1 << pos) + 1]));
    }

    return 0;
}
