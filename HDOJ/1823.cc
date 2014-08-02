/*
 *  SRC: HDOJ 1823
 * PROB: Luck and Love
 * ALGO: Segment tree
 * DATE: Aug 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const double eps = 1e-6;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return x << 1 | 1; }

class Segment_tree {
    private:
        static const int lep = 0, rep = 1001;
        int val[1001 << 2];

    public:
        void build()
        {
            memset(val, 0xff, sizeof val);
        }

        void update(int p, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                val[idx] = max(val[idx], v);
                return ;
            }

            int mid = (a + b) >> 1;
            if (p < mid) update(p, v, a, mid, LC(idx));
            else update(p, v, mid, b, RC(idx));

            val[idx] = max(val[LC(idx)], val[RC(idx)]);
        }

        int query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return val[idx];
            }

            int mid = (a + b) >> 1;
            int lr = -1, rr = -1;
            if (c < mid) lr = query(c, d, a, mid, LC(idx));
            if (d > mid) rr = query(c, d, mid, b, RC(idx));
            return max(lr, rr);
        }
};

class Segment_tree_2D {
    private:
        static const int lep = 100, rep = 201;
        Segment_tree val[101 << 2];

    public:
        void build(int a = lep, int b = rep, int idx = 1)
        {
            val[idx].build();
            if (a + 1 < b) {
                int mid = (a + b) >> 1;
                build(a, mid, LC(idx));
                build(mid, b, RC(idx));
            }
        }

        void update(int p, int v, int l, int a = lep, int b = rep, int idx = 1)
        {
            val[idx].update(v, l);
            if (a + 1 < b) {
                int mid = (a + b) >> 1;
                if (p < mid) update(p, v, l, a, mid, LC(idx));
                else update(p, v, l, mid, b, RC(idx));
            }
        }

        int query(int c, int d, int v1, int v2, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return val[idx].query(v1, v2);
            }

            int mid = (a + b) >> 1;
            int lr = -1, rr = -1;
            if (c < mid) lr = query(c, d, v1, v2, a, mid, LC(idx));
            if (d > mid) rr = query(c, d, v1, v2, mid, b, RC(idx));
            return max(lr, rr);
        }
} st;

int main()
{
    int m;
    while (scanf("%d", &m), m) {
        st.build();
        for (int i = 0; i < m; i++) {
            char c;
            scanf(" %c", &c);
            if (c == 'I') {
                int h;
                double a, l;
                scanf("%d%lf%lf", &h, &a, &l);
                st.update(h, a * 10 + eps, l * 10 + eps);
            } else {
                int h1, h2;
                double a1, a2;
                scanf("%d%d%lf%lf", &h1, &h2, &a1, &a2);
                if (h1 > h2) swap(h1, h2);
                if (a1 > a2) swap(a1, a2);
                int r = st.query(h1, h2 + 1, a1 * 10 + eps, a2 * 10 + 1 + eps);
                if (r == -1) puts("-1");
                else printf("%.1f\n", r / 10.0);
            }
        }
    }

    return 0;
}

