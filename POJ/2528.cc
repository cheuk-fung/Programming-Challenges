/*
 *  SRC: POJ 2528
 * PROB: Mayor's posters
 * ALGO: Segment Tree
 * DATE: Jul 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

struct Node {
    int a, b;
    int cover;
    Node* lc;
    Node* rc;

    Node()
        : cover(0), lc(0), rc(0)
    { }
};
Node* SegTree;

Node* SegTreeMake(int a, int b)
{
    Node* p = new Node;
    p->a = a;
    p->b = b;
    return p;
}

void SegTreeInsert(Node* p, int c, int d, int type)
{
    if (c <= p->a && p->b <= d) {
        p->cover = type;

        return ;
    }

    if (!p->lc) p->lc = SegTreeMake(p->a, (p->a + p->b) / 2);
    if (!p->rc) p->rc = SegTreeMake((p->a + p->b) / 2, p->b);

    if (p->cover) {
        p->lc->cover = p->rc->cover = p->cover;
        p->cover = 0;
    }

    if (c < (p->a + p->b) / 2) SegTreeInsert(p->lc, c, d, type);
    if (d > (p->a + p->b) / 2) SegTreeInsert(p->rc, c, d, type);
}

bool visible[10010];

void count(Node* p)
{
    if (p->cover) {
        visible[p->cover - 1] = 1;

        return ;
    }

    if (p->lc) count(p->lc);
    if (p->rc) count(p->rc);
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        SegTree = SegTreeMake(0, 10000000);

        for (int i = 0; i < n; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            SegTreeInsert(SegTree, l - 1, r, i + 1);
        }

        memset(visible, 0, sizeof(visible));
        count(SegTree);

        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (visible[i]) cnt++;

        printf("%d\n", cnt);

        delete SegTree;
    }

    return 0;
}
