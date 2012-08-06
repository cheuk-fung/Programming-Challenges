/*
 *  SRC: POJ 3667
 * PROB: Hotel
 * ALGO: Segment tree
 * DATE: Aug 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int l, r;
            int mx;
        } node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            node[idx].mx = max(node[LC(idx)].r + node[RC(idx)].l, max(node[LC(idx)].mx, node[RC(idx)].mx));

            int mid = (a + b) >> 1;
            node[idx].l = node[LC(idx)].l;
            if (node[LC(idx)].l == mid - a) node[idx].l += node[RC(idx)].l;
            node[idx].r = node[RC(idx)].r;
            if (node[RC(idx)].r == b - mid) node[idx].r += node[LC(idx)].r;
        }

        void push_down(int a, int b, int idx)
        {
            if (node[idx].mx == b - a) {
                int mid = (a + b) >> 1;
                node[LC(idx)].mx = node[LC(idx)].l = node[LC(idx)].r = mid - a;
                node[RC(idx)].mx = node[RC(idx)].l = node[RC(idx)].r = b - mid;
            } else if (node[idx].mx == 0) {
                node[LC(idx)].mx = node[LC(idx)].l = node[LC(idx)].r = 0;
                node[RC(idx)].mx = node[RC(idx)].l = node[RC(idx)].r = 0;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                if (v == 0) {
                    node[idx].l = node[idx].r = b - a;
                    node[idx].mx = b - a;
                } else {
                    node[idx].l = node[idx].r = 0;
                    node[idx].mx = 0;
                }
                return ;
            }

            push_down(a, b, idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid ,b, RC(idx));

            push_up(a, b, idx);
        }

        int query(int len, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) return a;
            push_down(a, b, idx);

            int mid = (a + b) >> 1;
            if (len <= node[LC(idx)].mx) return query(len, a, mid, LC(idx));
            if (len <= node[LC(idx)].r + node[RC(idx)].l) return mid - node[LC(idx)].r;
            if (len <= node[RC(idx)].mx) return query(len, mid, b, RC(idx));
            return 0;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    st.build(1, n + 1);
    st.update(1, n + 1, 0);

    while (m--) {
        int opr;
        scanf("%d", &opr);
        if (opr == 1) {
            int d;
            scanf("%d", &d);
            int r = st.query(d);
            printf("%d\n", r);
            if (r) st.update(r, r + d, 1);
        } else {
            int x, d;
            scanf("%d%d", &x, &d);
            st.update(x, x + d, 0);
        }
    }

    return 0;
}

