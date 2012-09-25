/*
 *  SRC: POJ 2823
 * PROB: Sliding Window
 * ALGO: Segment Tree
 * DATE: Jul 20, 2011 
 * COMP: C++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int INF = 0x3FFFFFFF;

inline int min(int a, int b)
{
    return a < b ? a : b;
}

inline int max(int a, int b)
{
    return a > b ? a : b;
}

struct Node {
    int a, b; // segment [a, b)
    int min, max;
};
Node SegTree[3000000];

void SegTreeMake(int p, int a, int b)
{
    SegTree[p].a = a;
    SegTree[p].b = b;
    SegTree[p].min = INF;
    SegTree[p].max = -INF;

    if (a + 1 < b) {
        SegTreeMake(p * 2, a, (a + b) / 2);
        SegTreeMake(p * 2 + 1, (a + b) / 2, b);
    }
}

void SegTreeInsert(int p, int c, int d, int v)
{
    if (c <= SegTree[p].a && SegTree[p].b <= d) {
        SegTree[p].min = min(SegTree[p].min, v);
        SegTree[p].max = max(SegTree[p].max, v);

        return ;
    }

    if (c < (SegTree[p].a + SegTree[p].b) / 2) SegTreeInsert(p * 2, c, d, v);
    if (d > (SegTree[p].a + SegTree[p].b) / 2) SegTreeInsert(p * 2 + 1, c, d, v);
    SegTree[p].min = min(SegTree[p].min, min(SegTree[p * 2].min, SegTree[p * 2 + 1].min));
    SegTree[p].max = max(SegTree[p].max, max(SegTree[p * 2].max, SegTree[p * 2 + 1].max));
}

void SegTreeQuery(int p, int c, int d, int* minVal, int* maxVal)
{
    if (c <= SegTree[p].a && SegTree[p].b <= d) {
        *minVal = SegTree[p].min;
        *maxVal = SegTree[p].max;
        return ;
    }

    int tmin1 = INF, tmin2 = INF, tmax1 = -INF, tmax2 = -INF;
    if (c < (SegTree[p].a + SegTree[p].b) / 2) SegTreeQuery(p * 2, c, d, &tmin1, &tmax1);
    if (d > (SegTree[p].a + SegTree[p].b) / 2) SegTreeQuery(p * 2 + 1, c, d, &tmin2, &tmax2);
    *minVal = min(tmin1, tmin2);
    *maxVal = max(tmax1, tmax2);
}

int n, k;
int minVal[1000000], maxVal[1000000];

int main()
{
    scanf("%d%d", &n, &k);

    SegTreeMake(1, 0, n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        SegTreeInsert(1, i, i + 1, a);
    }

    for (int i = 0; i + k <= n; i++)
        SegTreeQuery(1, i, i + k, minVal + i, maxVal + i);

    printf("%d", minVal[0]);
    for (int i = 1; i + k <= n; i++) {
        printf(" %d", minVal[i]);
    }
    putchar(10);

    printf("%d", maxVal[0]);
    for (int i = 1; i + k <= n; i++) {
        printf(" %d", maxVal[i]);
    }
    putchar(10);

    return 0;
}

