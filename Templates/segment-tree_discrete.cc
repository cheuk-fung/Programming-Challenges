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

using namespace std;

const double eps = 1e-8;
const int MAXN = 10010;
const int INF = 0x3FFFFFFF;

inline bool eq(double a, double b) { return fabs(a - b) < eps; }
inline bool ls(double a, double b) { return a + eps < b; }
inline int LC(int x) { return x << 1; }
inline int RC(int x) { return (x << 1) | 1; }

class Segment_Tree {
    private:
        struct Tnode {
            int a, b;
            int v, mx;
        };
        Tnode node[MAXN * 20];

    public:
        void build(int a, int b, int idx = 1)
        {
            node[idx].a = a;
            node[idx].b = b;
            node[idx].v = 0;
            node[idx].mx = -INF;

            if (a + 1 < b) {
                build(a, (a + b) >> 1, LC(idx));
                build((a + b) >> 1, b, RC(idx));
            }
        }

        void insert(int c, int d, int v, int idx = 1)
        {
            if (c <= node[idx].a && node[idx].b <= d) {
                node[idx].v += v;
                node[idx].mx = max(node[LC(idx)].mx, node[RC(idx)].mx) \
                               + node[idx].v;
                return ;
            }

            if (c < (node[idx].a + node[idx].b) >> 1) insert(c, d, v, LC(idx));
            if (d > (node[idx].a + node[idx].b) >> 1) insert(c, d, v, RC(idx));
            node[idx].mx = max(node[LC(idx)].mx, node[RC(idx)].mx) \
                           + node[idx].v;
        }

        int query()
        {
            return node[1].mx;
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

    bool operator<(const Segment &other) const
    {
        if (eq(x, other.x)) { return v < other.v; }
        return x < other.x;
    }
};

Segment_Tree st;
Point p[MAXN];
Discrete dy[MAXN * 2];
Segment seg[MAXN * 2];

int main()
{
    int n, W, H;
    while (scanf("%d%d%d", &n, &W, &H) != EOF) {
        double dw = W / 2.0, dh = H / 2.0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].v);
            dy[LC(i)].id = LC(i);
            dy[LC(i)].y = p[i].y - dh;
            dy[RC(i)].id = RC(i);
            dy[RC(i)].y = p[i].y + dh;
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
            seg[LC(i)].x = p[i].x - dw;
            seg[LC(i)].b = dy[LC(i)].new_y;
            seg[LC(i)].e = dy[RC(i)].new_y;
            seg[LC(i)].v = p[i].v;

            seg[RC(i)].x = p[i].x + dw;
            seg[RC(i)].b = dy[LC(i)].new_y;
            seg[RC(i)].e = dy[RC(i)].new_y;
            seg[RC(i)].v = -p[i].v;
        }
        sort(seg, seg + n * 2);

        int ans = -INF;
        st.build(0, cnt + 1);
        for (int i = 0; i < n * 2; i++) {
            st.insert(seg[i].b, seg[i].e, seg[i].v);
            ans = max(ans, st.query());
        }

        printf("%d\n", ans);
    }

    return 0;
}
