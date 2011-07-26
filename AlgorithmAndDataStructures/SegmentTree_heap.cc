/*
 *  SRC: POJ 3264
 * PROB: Balanced Lineup
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

inline int fmin(int a, int b)
{
    return a < b ? a : b;
}

inline int fmax(int a, int b)
{
    return a > b ? a : b;
}

class SegTree
{
    private:
        const static int INF = 0x3FFFFFFF;

        struct Node {
            int a, b;
            int min, max;
        };

        Node buf[200000];

    public:
        void build(int a, int b, int p = 1)
        {
            buf[p].a = a;
            buf[p].b = b;
            buf[p].min = INF;
            buf[p].max = -INF;

            if (a + 1 < b) {
                build(a, (a + b) / 2, p * 2);
                build((a + b) / 2, b, p * 2 + 1);
            }
        }

        void insert(int c, int d, int v, int p = 1)
        {
            if (c <= buf[p].a && buf[p].b <= d) {
                buf[p].min = fmin(buf[p].min, v);
                buf[p].max = fmax(buf[p].max, v);
                return ;
            }

            if (c < (buf[p].a + buf[p].b) / 2) insert(c, d, v, p * 2);
            if (d > (buf[p].a + buf[p].b) / 2) insert(c, d, v, p * 2 + 1);
            buf[p].min = fmin(buf[p * 2].min, buf[p * 2 + 1].min);
            buf[p].max = fmax(buf[p * 2].max, buf[p * 2 + 1].max);
        }

        void query(int c, int d, int* minVal, int* maxVal, int p = 1)
        {
            if (c <= buf[p].a && buf[p].b <= d) {
                *minVal = buf[p].min;
                *maxVal = buf[p].max;
                return ;
            }

            int tlmin = INF, tlmax = -INF, trmin = INF, trmax = -INF;
            if (c < (buf[p].a + buf[p].b) / 2) query(c, d, &tlmin, &tlmax, p * 2);
            if (d > (buf[p].a + buf[p].b) / 2) query(c, d, &trmin, &trmax, p * 2 + 1);
            *minVal = fmin(tlmin, trmin);
            *maxVal = fmax(tlmax, trmax);
        }
};

SegTree st;

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);

    st.build(0, n);

    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
        st.insert(i, i + 1, h);
    }

    for (int i = 0; i< q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        int min, max;
        st.query(a - 1, b, &min, &max);

        printf("%d\n", max - min);
    }

    return 0;
}
