/*
 *  SRC: POJ 2482
 * PROB: Stars in Your Window
 * ALGO: Segment Tree
 * DATE: Sep 07, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;

const double eps = 1e-8;
const int MAX_N = 10010;
const int INF = 0x3FFFFFFF;

inline int fmax(int a, int b) { return a > b ? a : b; }
inline bool eq(double a, double b) { return fabs(a - b) < eps; }
inline bool ls(double a, double b) { return a + eps < b; }

class SegTree {
    private:
        struct Tnode {
            int a, b;
            int v, max;
        };
        Tnode node[MAX_N * 20];

    public:
        void build(int a, int b, int p = 1)
        {
            node[p].a = a;
            node[p].b = b;
            node[p].v = 0;
            node[p].max = -INF;

            if (a + 1 < b) {
                build(a, (a + b) / 2, p * 2);
                build((a + b) / 2, b, p * 2 + 1);
            }
        }

        void insert(int c, int d, int v, int p = 1)
        {
            if (c <= node[p].a && node[p].b <= d) {
                node[p].v += v;
                node[p].max = fmax(node[p * 2].max, node[p * 2 + 1].max) \
                              + node[p].v;
                return ;
            }

            if (c < (node[p].a + node[p].b) / 2) insert(c, d, v, p * 2);
            if (d > (node[p].a + node[p].b) / 2) insert(c, d, v, p * 2 + 1);
            node[p].max = fmax(node[p * 2].max, node[p * 2 + 1].max) \
                          + node[p].v;
        }

        int query()
        {
            return node[1].max;
        }
};

struct Point {
    int x, y, v;
};

struct Discrete {
    double y;
    int id, new_y;
};

inline bool cmp_y(const Discrete &a, const Discrete &b) { return ls(a.y, b.y); }
inline bool cmp_id(const Discrete &a, const Discrete &b) { return a.id < b.id; }

struct Segment {
    double x;
    int b, e, v;

    bool operator <(const Segment &other) const
    {
        if (eq(x, other.x)) { return v < other.v; }
        return x < other.x;
    }
};

SegTree st;
Point p[MAX_N];
Discrete dy[MAX_N * 2];
Segment seg[MAX_N * 2];

int main()
{
    int n, W, H;
    while (scanf("%d%d%d", &n, &W, &H) != EOF) {
        double dw = W / 2.0, dh = H / 2.0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].v);
            dy[i * 2].id = i * 2;
            dy[i * 2].y = p[i].y - dh;
            dy[i * 2 + 1].id = i * 2 + 1;
            dy[i * 2 + 1].y = p[i].y + dh;
        }

        sort(dy, dy + n * 2, cmp_y);
        dy[0].new_y = 0;
        int cnt = 0;
        for (int i = 1; i < n * 2; i++) {
            if (!eq(dy[i].y, dy[i - 1].y)) cnt++;
            dy[i].new_y = cnt;
        }
        sort(dy, dy + n * 2, cmp_id);

        for (int i = 0; i < n; i++) {
            seg[i * 2].x = p[i].x - dw;
            seg[i * 2].b = dy[i * 2].new_y;
            seg[i * 2].e = dy[i * 2 + 1].new_y;
            seg[i * 2].v = p[i].v;

            seg[i * 2 + 1].x = p[i].x + dw;
            seg[i * 2 + 1].b = dy[i * 2].new_y;
            seg[i * 2 + 1].e = dy[i * 2 + 1].new_y;
            seg[i * 2 + 1].v = -p[i].v;
        }
        sort(seg, seg + n * 2);

        int ans = -INF;
        st.build(0, cnt + 1);
        for (int i = 0; i < n * 2; i++) {
            st.insert(seg[i].b, seg[i].e, seg[i].v);
            ans = fmax(ans, st.query());
        }

        printf("%d\n", ans);
    }

    return 0;
}
