/*
 *  SRC: HDOJ 1698
 * PROB: Just a Hook
 * ALGO: Segment tree
 * DATE: Aug 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXN = 100010;

class Segment_tree {
    private:
        static int lep, rep;
        int val[MAXN << 2];
        int color[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int idx)
        {
            val[idx] = val[LC(idx)] + val[RC(idx)];
        }

        void push_down(int a, int b, int idx)
        {
            if (color[idx]) {
                int mid = (a + b) >> 1;
                val[LC(idx)] = (mid - a) * color[idx];
                val[RC(idx)] = (b - mid) * color[idx];
                color[LC(idx)] = color[RC(idx)] = color[idx];
                color[idx] = 0;
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
            if (color[idx] == v) return ;
            if (c <= a && b <= d) {
                val[idx] = (b - a) * v;
                color[idx] = v;
                return ;
            }

            push_down(a, b, idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));

            push_up(idx);
        }

        int query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return val[idx];
            }

            int mid = (a + b) >> 1, res = 0;
            if (c < mid) res += query(c, d, a, mid, LC(idx));
            if (d > mid) res += query(c, d, mid, b, RC(idx));
            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        st.build(0, n);
        for (int i = 0; i < n; i++) {
            st.update(i, i + 1, 1);
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            st.update(x - 1, y, z);
        }

        int r = st.query(0, n);
        printf("Case %d: The total value of the hook is %d.\n", task, r);
    }

    return 0;
}

