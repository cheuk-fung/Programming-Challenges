/*
ID: os.idea1
LANG: C++
TASK: picture
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using std::sort;

class SegTree {
    private:
        struct Tnode {
            int a, b; // segment [a, b)
            int cover;
            int len;
            Tnode* lc;
            Tnode* rc;

            Tnode(int _a, int _b)
                : a(_a), b(_b), cover(0), len(0), lc(0), rc(0)
            { }
        };
        Tnode* root;

        Tnode* build(int a, int b)
        {
            Tnode* p = new Tnode(a, b);

            return p;
        }

        void _insert(int c, int d, int delta, Tnode* p)
        {
            if (c <= p->a && p->b <= d) p->cover += delta;
            else {
                if (!p->lc) {
                    p->lc = new Tnode(p->a, (p->a + p->b) / 2);
                    p->rc = new Tnode((p->a + p->b) / 2, p->b);
                }
                if (c < (p->a + p->b) / 2) _insert(c, d, delta, p->lc);
                if (d > (p->a + p->b) / 2) _insert(c, d, delta, p->rc);
            }

            if (p->cover) p->len = p->b - p->a;
            else if (p->lc) p->len = p->lc->len + p->rc->len;
            else p->len = 0;
        }

    public:
        SegTree(int l, int r)
        {
            root = build(l, r);
        }

        void insert(int c, int d, int delta)
        {
            _insert(c, d, delta, root);
        }

        int query()
        {
            return root->len;
        }

};

struct Line {
    int x, y1, y2;
    int delta;

    bool operator < (const Line& other) const
    {
        if (x == other.x) return delta > other.delta;
        return x < other.x;
    }
};

Line X[10010], Y[10010];

int main()
{
    FILE *fin  = fopen("picture.in", "r"),
         *fout = fopen("picture.out", "w");

    int n;
    fscanf(fin, "%d", &n);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        fscanf(fin, "%d%d%d%d", &x1, &y1, &x2, &y2);
        X[cnt].x = x1; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt].delta = 1;
        Y[cnt].x = y1; Y[cnt].y1 = x1; Y[cnt].y2 = x2; Y[cnt++].delta = 1;

        X[cnt].x = x2; X[cnt].y1 = y1; X[cnt].y2 = y2; X[cnt].delta = -1;
        Y[cnt].x = y2; Y[cnt].y1 = x1; Y[cnt].y2 = x2; Y[cnt++].delta = -1;
    }

    sort(X, X + cnt);
    sort(Y, Y + cnt);

    int ans = 0;
    SegTree st_x(-10000, 10001);
    for (int i = 0, curr = 0; i < cnt; i++) {
        st_x.insert(X[i].y1, X[i].y2, X[i].delta);
        ans += abs(curr - st_x.query());
        curr = st_x.query();
    }

    SegTree st_y(-10000, 10001);
    for (int i = 0, curr = 0; i < cnt; i++) {
        st_y.insert(Y[i].y1, Y[i].y2, Y[i].delta);
        ans += abs(curr - st_y.query());
        curr = st_y.query();
    }

    fprintf(fout, "%d\n", ans);

    return 0;
}
