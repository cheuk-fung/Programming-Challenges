/*
 *  SRC: POJ 3264
 * PROB: Balanced Lineup
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int INF = 0x3FFFFFFF;

inline int fmin(int a, int b)
{
    return a < b ? a : b;
}

inline int fmax(int a, int b)
{
    return a > b ? a : b;
}

struct Node {
    int a, b;
    int min, max;
} SegTree[200000];

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
        SegTree[p].min = fmin(SegTree[p].min, v);
        SegTree[p].max = fmax(SegTree[p].max, v);
        return ;
    }

    if (c < (SegTree[p].a + SegTree[p].b) / 2) SegTreeInsert(p * 2, c, d, v);
    if (d > (SegTree[p].a + SegTree[p].b) / 2) SegTreeInsert(p * 2 + 1, c, d, v);
    SegTree[p].min = fmin(SegTree[p * 2].min, SegTree[p * 2 + 1].min);
    SegTree[p].max = fmax(SegTree[p * 2].max, SegTree[p * 2 + 1].max);
}

void SegTreeQuery(int p, int c, int d, int* minVal, int* maxVal)
{
    if (c <= SegTree[p].a && SegTree[p].b <= d) {
        *minVal = SegTree[p].min;
        *maxVal = SegTree[p].max;
        return ;
    }

    int tlmin = INF, tlmax = -INF, trmin = INF, trmax = -INF;
    if (c < (SegTree[p].a + SegTree[p].b) / 2) SegTreeQuery(p * 2, c, d, &tlmin, &tlmax);
    if (d > (SegTree[p].a + SegTree[p].b) / 2) SegTreeQuery(p * 2 + 1, c, d, &trmin, &trmax);
    *minVal = fmin(tlmin, trmin);
    *maxVal = fmax(tlmax, trmax);
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    
    SegTreeMake(1, 0, n);

    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
        SegTreeInsert(1, i, i + 1, h);
    }

    for (int i = 0; i< q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        int min, max;
        SegTreeQuery(1, a - 1, b, &min, &max);

        printf("%d\n", max - min);
    }


    return 0;
}
