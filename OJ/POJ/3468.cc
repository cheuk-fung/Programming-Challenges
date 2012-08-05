/*
 *  SRC: POJ 3468
 * PROB: A Simple Problem with Integers
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
        long long val[MAXN << 2];
        long long offset[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }
        void push_up(int idx) { val[idx] = val[LC(idx)] + val[RC(idx)]; }
        void push_down(int a, int b, int idx)
        {
            if (offset[idx]) {
                int mid = (a + b) >> 1;
                val[LC(idx)] += (mid - a) * offset[idx];
                val[RC(idx)] += (b - mid) * offset[idx];
                offset[LC(idx)] += offset[idx];
                offset[RC(idx)] += offset[idx];
                offset[idx] = 0;
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int c, int d, long long v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                val[idx] += (b - a) * v;
                offset[idx] += v;
                return ;
            }

            push_down(a, b, idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));

            push_up(idx);
        }

        long long query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return val[idx];
            }

            push_down(a, b, idx);

            long long res = 0;
            int mid = (a + b) >> 1;
            if (c < mid) res += query(c, d, a, mid, LC(idx));
            if (d > mid) res += query(c, d, mid, b, RC(idx));
            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    st.build(0, n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        st.update(i, i + 1, a);
    }

    while (q--) {
        char c;
        scanf(" %c", &c);
        if (c == 'C') {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            st.update(a - 1, b, c);
        } else {
            int a, b;
            scanf("%d%d", &a, &b);
            long long r = st.query(a - 1, b);
            printf("%lld\n", r);
        }
    }

    return 0;
}

