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

inline int fmin(int a, int b) { return a < b ? a : b; }
inline int fmax(int a, int b) { return a > b ? a : b; }

class SegTree {
    private:
        const static int INF = 0x3FFFFFFF;

        struct Tnode {
            int a, b;
            int min, max;
        };
        Tnode node[200000];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx].a = a;
            node[idx].b = b;
            node[idx].min = INF;
            node[idx].max = -INF;

            if (a + 1 < b) {
                build(a, (a + b) / 2, idx * 2);
                build((a + b) / 2, b, idx * 2 + 1);
            }
        }

        void insert(int c, int d, int v, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                node[idx].min = fmin(node[idx].min, v);
                node[idx].max = fmax(node[idx].max, v);
                return ;
            }

            if (c < (node[idx].a + node[idx].b) / 2) insert(c, d, v, idx * 2);
            if (d > (node[idx].a + node[idx].b) / 2) insert(c, d, v, idx * 2 + 1);
            node[idx].min = fmin(node[idx * 2].min, node[idx * 2 + 1].min);
            node[idx].max = fmax(node[idx * 2].max, node[idx * 2 + 1].max);
        }

        void query(int c, int d, int* minVal, int* maxVal, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                *minVal = node[idx].min;
                *maxVal = node[idx].max;
                return ;
            }

            int tlmin = INF, tlmax = -INF, trmin = INF, trmax = -INF;
            if (c < (node[idx].a + node[idx].b) / 2) query(c, d, &tlmin, &tlmax, idx * 2);
            if (d > (node[idx].a + node[idx].b) / 2) query(c, d, &trmin, &trmax, idx * 2 + 1);
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
