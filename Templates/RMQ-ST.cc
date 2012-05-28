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
#include <cstring>
#include <cmath>
#include <algorithm>

using std::max;
using std::min;

const int MAXN = 50010;
int height[MAXN];
int mx[20][MAXN], mn[20][MAXN];

void RMQ_init(int *a, int n)
{
    memcpy(mx[0], a, sizeof(int) * n);
    memcpy(mn[0], a, sizeof(int) * n);
    for (int i = 1; 1 << i <= n; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            mx[i][j] = max(mx[i - 1][j], mx[i - 1][j + (1 << (i - 1))]);
            mn[i][j] = min(mn[i - 1][j], mn[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int RMQ_max(int l, int r) // [l, r)
{
    int idx = log2(r - l);
    return max(mx[idx][l], mx[idx][r - (1 << idx)]);
}

int RMQ_min(int l, int r) // [l, r)
{
    int idx = log2(r - l);
    return min(mn[idx][l], mn[idx][r - (1 << idx)]);
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", height + i);
    }

    RMQ_init(height, n);

    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r); // [l, r], starting from 1
        printf("%d\n", RMQ_max(l - 1, r) - RMQ_min(l - 1, r));
    }

    return 0;
}
