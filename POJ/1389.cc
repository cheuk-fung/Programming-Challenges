/*
 *  SRC: POJ 1389
 * PROB: Area of Simple Polygons
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

struct Node {
    int a, b; // segment [a, b)
    int cover, len;
    Node* lc;
    Node* rc;

    Node(int _a, int _b)
        : a(_a), b(_b), cover(0), len(0), lc(0), rc(0)
    { }
};
Node* SegTree;

void SegTreeInsert(Node* p, int c, int d, int delta)
{
    if (c <= p->a && p->b <= d) p->cover += delta;
    else {
        if (!p->lc) {
            p->lc = new Node(p->a, (p->a + p->b) / 2);
            p->rc = new Node((p->a + p->b) / 2, p->b);
        }
        if (c < (p->a + p->b) / 2) SegTreeInsert(p->lc, c, d, delta);
        if (d > (p->a + p->b) / 2) SegTreeInsert(p->rc, c, d, delta);
    }

    if (p->cover) p->len = p->b - p->a;
    else if (p->lc) p->len = p->lc->len + p->rc->len;
    else p->len = 0;
}

struct Line {
    int x, y1, y2;
    int delta;

    bool operator < (const Line& other) const
    {
        return x < other.x;
    }
};

inline int fmax(int a, int b)
{
    return a > b ? a : b;
}

Line X[2012];

int main()
{
    int x1, y1, x2, y2;
    while (1 + 1 == 2) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 == -1 && y2 == -1 && x2 == -1 && y2 == -1) break;

        int cnt = 0, maxY = 0;
        while (1 + 1 == 2) {
            if (x1 == -1 && y2 == -1 && x2 == -1 && y2 == -1) break;

            X[cnt].x = x1; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt++].delta = 1;
            X[cnt].x = x2; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt++].delta = -1;

            maxY = fmax(maxY, fmax(y1, y2));

            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        }

        sort(X, X + cnt);

        int ans = 0;
        SegTree = new Node(0, maxY + 1);
        for (int i = 0, preL = 0, preX = 0; i < cnt; i++) {
            SegTreeInsert(SegTree, X[i].y1, X[i].y2, X[i].delta);
            ans += preL * (X[i].x - preX);
            preL = SegTree->len;
            preX = X[i].x;
        }

        printf("%d\n", ans);
    }

    return 0;
}

