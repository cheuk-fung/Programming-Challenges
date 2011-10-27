/*
 *  SRC: POJ 2777
 * PROB: Count Color
 * ALGO: Segment Tree
 * DATE: Jul 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

struct Node {
    int a, b; // segment [a, b)
    int cover;
    int pure;
    Node* lc;
    Node* rc;

    Node(int _a, int _b)
        : a(_a), b(_b), cover(1), pure(1), lc(0), rc(0)
    { }
};
Node* SegTree;

void SegTreeMake(Node* p, int a, int b)
{
    if (a + 1 < b) {
        p->lc = new Node(a, (a + b) / 2);
        SegTreeMake(p->lc, a, (a + b) / 2);

        p->rc = new Node((a + b) / 2, b);
        SegTreeMake(p->rc, (a + b) / 2, b);
    }
}

void SegTreeInsert(Node* p, int c, int d, int color)
{
    if (c <= p->a && p->b <= d) {
        p->pure = 1;
        p->cover = color;

        return ;
    }

    if (p->pure) {
        p->pure = 0;

        p->lc->cover = p->cover;
        p->lc->pure = 1;

        p->rc->cover = p->cover;
        p->rc->pure = 1;
    }

    if (c < (p->a + p->b) / 2) SegTreeInsert(p->lc, c, d, color);
    if (d > (p->a + p->b) / 2) SegTreeInsert(p->rc, c, d, color);
    p->cover = p->lc->cover | p->rc->cover;
}

int SegTreeCount(Node* p, int c, int d)
{
    if ((c <= p->a && p->b <= d) || p->pure)
        return p->cover;

    int res = 0;
    if (c < (p->a + p->b) / 2) res |= SegTreeCount(p->lc, c, d);
    if (d > (p->a + p->b) / 2) res |= SegTreeCount(p->rc, c, d);

    return res;
}

int main()
{
    int l, t, o;
    scanf("%d%d%d", &l, &t, &o);

    SegTree = new Node(1, l + 1);
    SegTreeMake(SegTree, 1, l + 1);

    for (int i = 0; i < o; i++) {
        char ctrl[10];
        int a, b;
        scanf("%s%d%d", ctrl, &a, &b);
        if (a > b) {
            int t = a;
            a = b;
            b = t;
        }
        if (ctrl[0] == 'C') {
            int c;
            scanf("%d", &c);
            SegTreeInsert(SegTree, a, b + 1, 1 << (c - 1));
        }
        else {
            int colors = SegTreeCount(SegTree, a, b + 1);
            int cnt = 0;
            while (colors) {
                cnt++;
                colors -= colors & -colors;
            }

            printf("%d\n", cnt);
        }
    }

    return 0;
}
