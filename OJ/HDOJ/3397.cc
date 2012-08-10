/*
 *  SRC: HDOJ 3397
 * PROB: Sequence operation
 * ALGO: Segment tree
 * DATE: Aug 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Tnode {
    int cover, XOR;
    int ones;        // Operation 3
    int mx, l, r;    // Operation 4

    void set(int _cover, int v)
    {
        cover = _cover;
        XOR = 0;
        ones = mx = l = r = v;
    }
};

class Segment_tree {
    private:
        static int lep, rep;
        Tnode node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void XOR(int a, int b, int idx)
        {
            if (node[idx].cover != -1) {
                if (node[idx].cover) {
                    node[idx].set(0, 0);
                } else {
                    node[idx].set(1, b - a);
                }
            } else {
                node[idx].XOR ^= 1;
            }
        }

        void push_up(Tnode &p, const Tnode &lc, const Tnode &rc)
        {
            p.ones = lc.ones + rc.ones;
            p.mx = max(lc.r + rc.l, max(lc.mx, rc.mx));
            p.l = lc.l + (lc.cover == 1) * rc.l;
            p.r = rc.r + (rc.cover == 1) * lc.r;

            p.XOR = 0;
            if (lc.cover == -1 || rc.cover == -1 || (lc.cover != rc.cover)) p.cover = -1;
            else p.cover = lc.cover;
        }

        void push_down(int a, int b, int idx)
        {
            int mid = (a + b) >> 1;
            if (node[idx].cover != -1) {
                if (node[idx].cover) {
                    node[LC(idx)].set(1, mid - a);
                    node[RC(idx)].set(1, b - mid);
                } else {
                    node[LC(idx)].set(0, 0);
                    node[RC(idx)].set(0, 0);
                }
                node[idx].cover = -1;
            } else if (node[idx].XOR) {
                XOR(a, mid, LC(idx));
                XOR(mid, b, RC(idx));
                node[idx].XOR = 0;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, int opr, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                switch (opr) {
                    case 0: node[idx].set(0, 0); break;
                    case 1: node[idx].set(1, b - a); break;
                    case 2: XOR(a, b, idx);
                }
                return ;
            }

            push_down(a, b, idx);
            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, opr, a, mid, LC(idx));
            if (d > mid) update(c, d, opr, mid, b, RC(idx));
            push_up(node[idx], node[LC(idx)], node[RC(idx)]);
        }

        Tnode query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d && node[idx].cover != -1) {
                return node[idx];
            }

            push_down(a, b, idx);
            int mid = (a + b) >> 1;
            Tnode res, lc, rc;
            lc.mx = rc.mx = -1;
            if (c < mid) lc = query(c, d, a, mid, LC(idx));
            if (d > mid) rc = query(c, d, mid, b, RC(idx));

            if (lc.mx == -1) res = rc;
            else if (rc.mx == -1) res = lc;
            else push_up(res, lc, rc);

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
            int v;
            scanf("%d", &v);
            st.update(i, i + 1, v);
        }
        while (m--) {
            int op, a, b;
            scanf("%d%d%d", &op, &a, &b);
            if (op < 3) {
                st.update(a, b + 1, op);
            } else {
                Tnode r = st.query(a, b + 1);
                printf("%d\n", op == 3 ? r.ones : r.mx);
            }
        }
    }

    return 0;
}

