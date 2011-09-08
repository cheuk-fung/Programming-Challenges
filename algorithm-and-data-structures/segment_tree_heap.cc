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

class SegTree {
    private:
        const static int INF = 0x3FFFFFFF;

        struct Tnode {
            int a, b;
            int min, max;
        };

        Tnode node[200000];

    public:
        void build(int a, int b, int p = 1)
        {
            node[p].a = a;
            node[p].b = b;
            node[p].min = INF;
            node[p].max = -INF;

            if (a + 1 < b) {
                build(a, (a + b) / 2, p * 2);
                build((a + b) / 2, b, p * 2 + 1);
            }
        }

        void insert(int c, int d, int v, int p = 1)
        {
            if (c <= node[p].a && node[p].b <= d) {
                node[p].min = fmin(node[p].min, v);
                node[p].max = fmax(node[p].max, v);
                return ;
            }

            if (c < (node[p].a + node[p].b) / 2) insert(c, d, v, p * 2);
            if (d > (node[p].a + node[p].b) / 2) insert(c, d, v, p * 2 + 1);
            node[p].min = fmin(node[p * 2].min, node[p * 2 + 1].min);
            node[p].max = fmax(node[p * 2].max, node[p * 2 + 1].max);
        }

        void query(int c, int d, int* minVal, int* maxVal, int p = 1)
        {
            if (c <= node[p].a && node[p].b <= d) {
                *minVal = node[p].min;
                *maxVal = node[p].max;
                return ;
            }

            int tlmin = INF, tlmax = -INF, trmin = INF, trmax = -INF;
            if (c < (node[p].a + node[p].b) / 2) query(c, d, &tlmin, &tlmax, p * 2);
            if (d > (node[p].a + node[p].b) / 2) query(c, d, &trmin, &trmax, p * 2 + 1);
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
