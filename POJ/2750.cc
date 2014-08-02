/*
 *  SRC: POJ 2750
 * PROB: Potted Flower
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, m;

struct Info {
    int v, l, r;
    int vlen, llen, rlen;
};

struct Node {
    int a, b; // segment [a, b)
    int sum;
    Info max;
    Info min;
};
Node ST[400000];

inline int fmax(int a, int b)
{
    return a > b ? a : b;
}

inline int greater(int a, int b)
{
    return a > b;
}

inline int less(int a, int b)
{
    return a < b;
}

void updateV(Info* p, Info* lc, Info* rc, int (*cmp)(int, int))
{
    if (cmp(lc->v, rc->v)) {
        p->v = lc->v;
        p->vlen = lc->vlen;
    }
    else {
        p->v = rc->v;
        p->vlen = rc->vlen;
    }

    if (lc->rlen + rc->llen < n && cmp(lc->r + rc->l, p->v)) {
        p->v = lc->r + rc->l;
        p->vlen = lc->rlen + rc->llen;
    }
}

void updateL(Info*p, Info* lc, Info* rc, int sum, int len, int (*cmp)(int, int))
{
    p->l = lc->l;
    p->llen = lc->llen;

    if (len + rc->llen < n && cmp(sum + rc->l, p->l)) {
        p->l = sum + rc->l;
        p->llen = len + rc->llen;
    }
}

void updateR(Info*p, Info* lc, Info* rc, int sum, int len, int (*cmp)(int, int))
{
    p->r = rc->r;
    p->rlen = rc->rlen;

    if (lc->rlen + len < n && cmp(lc->r + sum, p->r)) {
        p->r = lc->r + sum;
        p->rlen = lc->rlen + len;
    }
}

void SegTreeMake(int p, int a, int b)
{
    ST[p].a = a;
    ST[p].b = b;

    if (a + 1 < b) {
        SegTreeMake(p * 2, a, (a + b) / 2);
        SegTreeMake(p * 2 + 1, (a + b) / 2, b);
    }
}

void SegTreeInsert(int p, int c, int d, int val)
{
    if (c <= ST[p].a && ST[p].b <= d) {
        ST[p].sum = val;

        ST[p].max.v = ST[p].max.l = ST[p].max.r = val;
        ST[p].max.vlen = ST[p].max.llen = ST[p].max.rlen = 1;

        ST[p].min.v = ST[p].min.l = ST[p].min.r = val;
        ST[p].min.vlen = ST[p].min.llen = ST[p].min.rlen = 1;

        return ;
    }

    if (c < (ST[p].a + ST[p].b) / 2) SegTreeInsert(p * 2, c, d, val);
    if (d > (ST[p].a + ST[p].b) / 2) SegTreeInsert(p * 2 + 1, c, d, val);

    ST[p].sum = ST[p * 2].sum + ST[p * 2 + 1].sum;

    updateV(&ST[p].max, &ST[p * 2].max, &ST[p * 2 + 1].max, greater);
    updateL(&ST[p].max, &ST[p * 2].max, &ST[p * 2 + 1].max, ST[p * 2].sum, ST[p * 2].b - ST[p * 2].a, greater);
    updateR(&ST[p].max, &ST[p * 2].max, &ST[p * 2 + 1].max, ST[p * 2 + 1].sum, ST[p * 2 + 1].b - ST[p * 2 + 1].a, greater);

    updateV(&ST[p].min, &ST[p * 2].min, &ST[p * 2 + 1].min, less);
    updateL(&ST[p].min, &ST[p * 2].min, &ST[p * 2 + 1].min, ST[p * 2].sum, ST[p * 2].b - ST[p * 2].a, less);
    updateR(&ST[p].min, &ST[p * 2].min, &ST[p * 2 + 1].min, ST[p * 2 + 1].sum, ST[p * 2 + 1].b - ST[p * 2 + 1].a, less);
}

int main()
{
    scanf("%d", &n);

    SegTreeMake(1, 0, n);

    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        SegTreeInsert(1, i, i + 1, v);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        SegTreeInsert(1, a - 1, a, b);
        printf("%d\n", fmax(ST[1].max.v, ST[1].sum - ST[1].min.v));
    }

    return 0;
}
