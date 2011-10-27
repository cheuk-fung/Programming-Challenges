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

inline int fmax(int a, int b)
{
    return a > b ? a : b;
}

inline int fmin(int a, int b)
{
    return a < b ? a : b;
}

int maxV[50010][20], minV[50010][20];

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &maxV[i][0]);
        minV[i][0] = maxV[i][0];
    }

    for (int j = 1; 1 << j <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            maxV[i][j] = fmax(maxV[i][j - 1], maxV[i + (1 << (j - 1))][j - 1]);
            minV[i][j] = fmin(minV[i][j - 1], minV[i + (1 << (j - 1))][j - 1]);
        }

    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int pos = log(r - l + 1.0) / log(2.0);
        printf("%d\n", fmax(maxV[l][pos], maxV[r - (1 << pos) + 1][pos]) - fmin(minV[l][pos], minV[r - (1 << pos) + 1][pos]));
    }

    return 0;
}
