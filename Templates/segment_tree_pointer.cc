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

class SegTree {
    private:
        struct Tnode {
            int a, b; // segment [a, b)
            int cover;
            int pure;
            Tnode* lc;
            Tnode* rc;

            Tnode(int _a, int _b)
                : a(_a), b(_b), cover(1), pure(1), lc(0), rc(0)
            { }
        };
        Tnode* root;

        Tnode* build(int a, int b)
        {
            Tnode* p = new Tnode(a, b);

            if (a + 1 < b) {
                p->lc = build(a, (a + b) / 2);
                p->rc = build((a + b) / 2, b);
            }

            return p;
        }

        void _insert(int c, int d, int color, Tnode* p)
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

            if (c < (p->a + p->b) / 2) _insert(c, d, color, p->lc);
            if (d > (p->a + p->b) / 2) _insert(c, d, color, p->rc);
            p->cover = p->lc->cover | p->rc->cover;
        }

        int _query(int c, int d, Tnode* p)
        {
            if ((c <= p->a && p->b <= d) || p->pure)
                return p->cover;

            int res = 0;
            if (c < (p->a + p->b) / 2) res |= _query(c, d, p->lc);
            if (d > (p->a + p->b) / 2) res |= _query(c, d, p->rc);

            return res;
        }

    public:
        SegTree(int l, int r)
        {
            root = build(l, r);
        }

        void insert(int c, int d, int color)
        {
            _insert(c, d, color, root);
        }

        int query(int c, int d)
        {
            return _query(c, d, root);
        }

};

int main()
{
    int l, t, o;
    scanf("%d%d%d", &l, &t, &o);

    SegTree st(1, l + 1);

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
            st.insert(a, b + 1, 1 << (c - 1));
        }
        else {
            int colors = st.query(a, b + 1);
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
