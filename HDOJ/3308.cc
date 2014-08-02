/*
 *  SRC: HDOJ 3308
 * PROB: LCIS
 * ALGO: Segment tree
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

int val[MAXN];

struct Tnode {
    int mx, l, r;
} node[MAXN << 2];

class Segment_tree {
    private:
        static int lep, rep;

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(Tnode &p, const Tnode &lc, const Tnode &rc, int a, int b)
        {
            int mid = (a + b) >> 1;
            p.l = lc.l;
            p.r = rc.r;
            p.mx = max(lc.mx, rc.mx);
            if (val[mid] > val[mid - 1]) {
                if (lc.l == mid - a) p.l += rc.l;
                if (rc.r == b - mid) p.r += lc.r;
                p.mx = max(p.mx, lc.r + rc.l);
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int p, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a == p && p + 1 == b) {
                node[idx].mx = node[idx].l = node[idx].r = 1;
                return ;
            }

            int mid = (a + b) >> 1;
            if (p < mid) update(p, v, a, mid, LC(idx));
            else update(p, v, mid ,b, RC(idx));
            push_up(node[idx], node[LC(idx)], node[RC(idx)], a, b);
        }

        Tnode query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return node[idx];
            }

            int mid = (a + b) >> 1;
            Tnode res, lc, rc;
            lc.mx = rc.mx = -1;
            if (c < mid) lc = query(c, d, a, mid, LC(idx));
            if (d > mid) rc = query(c, d, mid, b, RC(idx));

            if (lc.mx == -1) res = rc;
            else if (rc.mx == -1) res = lc;
            else push_up(res, lc, rc, a, b);

            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);
        st.build(0, n);
        for (int i = 0; i < n; i++) {
            scanf("%d", val + i);
            st.update(i, val[i]);
        }

        while (m--) {
            char c;
            int a, b;
            scanf(" %c%d%d", &c, &a, &b);
            if (c == 'U') {
                val[a] = b;
                st.update(a, b);
            } else {
                int r = st.query(a, b + 1).mx;
                printf("%d\n", r);
            }
        }
    }

    return 0;
}

