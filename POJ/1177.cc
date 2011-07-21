/*
 *  SRC: POJ 1177
 * PROB: Picture
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
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

Line X[10010], Y[10010];

int main()
{
    int n;
    scanf("%d", &n);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        X[cnt].x = x1; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt].delta = 1;
        Y[cnt].x = y1; Y[cnt].y1 = x1; Y[cnt].y2 = x2; Y[cnt++].delta = 1;

        X[cnt].x = x2; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt].delta = -1;
        Y[cnt].x = y2; Y[cnt].y1 = x1; Y[cnt].y2 = x2; Y[cnt++].delta = -1;
    }

    sort(X, X + cnt);
    sort(Y, Y + cnt);

    int ans = 0;
    SegTree = new Node(-10000, 10001);
    for (int i = 0, curr = 0; i < cnt; i++) {
        SegTreeInsert(SegTree, X[i].y1, X[i].y2, X[i].delta);
        ans += abs(curr - SegTree->len);
        curr = SegTree->len;
    }

    SegTree = new Node(-10000, 10001);
    for (int i = 0, curr = 0; i < cnt; i++) {
        SegTreeInsert(SegTree, Y[i].y1, Y[i].y2, Y[i].delta);
        ans += abs(curr - SegTree->len);
        curr = SegTree->len;
    }

    printf("%d\n", ans);

    return 0;
}
