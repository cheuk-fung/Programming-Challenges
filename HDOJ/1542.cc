/*
 *  SRC: HDOJ 1542
 * PROB: Atlantis
 * ALGO: Segment tree
 * DATE: Aug 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 210;
const double eps = 1e-6;

inline bool ls(double x, double y) { return x + eps < y; }

double len[MAXN];

struct Point {
    double x, y;
    int id;
    int ny;
} pnt[MAXN];
bool cmpy(const Point &a, const Point &b) { return ls(a.y, b.y); }
bool cmpid(const Point &a, const Point &b) { return ls(a.id, b.id); }

struct Segment {
    double x;
    int l, r;
    int v;

    bool operator<(const Segment &o) const { return ls(x, o.x); }
} seg[MAXN];

class Segment_tree {
    private:
        static int lep, rep;
        int cover[MAXN << 2];
        double val[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }
        void push_up(int a, int b, int idx)
        {
            if (cover[idx]) {
                val[idx] = len[b] - len[a];
            } else if (a + 1 < b) {
                val[idx] = val[LC(idx)] + val[RC(idx)];
            } else {
                val[idx] = 0;
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
                cover[idx] += v;
                push_up(a, b, idx);
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));
            push_up(a, b, idx);
        }

        double query() { return val[1]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int n, task = 1;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            pnt[i << 1] = (Point){x1, y1, i << 1};
            pnt[i << 1 | 1] = (Point){x2, y2, i << 1 | 1};
        }

        sort(pnt, pnt + 2 * n, cmpy);
        int idx = 0;
        pnt[0].ny = 0;
        for (int i = 1; i < 2 * n; i++) {
            if (ls(pnt[i - 1].y, pnt[i].y)) {
                idx++;
                len[idx] = len[idx - 1] + pnt[i].y - pnt[i - 1].y;
            }
            pnt[i].ny = idx;
        }

        sort(pnt, pnt + 2 * n, cmpid);
        for (int i = 0; i < 2 * n; i += 2) {
            seg[i] = (Segment){pnt[i].x, pnt[i].ny, pnt[i + 1].ny, 1};
            seg[i + 1] = (Segment){pnt[i + 1].x, pnt[i].ny, pnt[i + 1].ny, -1};
        }
        sort(seg, seg + 2 * n);

        st.build(0, idx + 1);
        double last = 0, area = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (i > 0) area += last * (seg[i].x - seg[i - 1].x);
            st.update(seg[i].l, seg[i].r, seg[i].v);
            last = st.query();
        }

        printf("Test case #%d\nTotal explored area: %.2f\n\n", task++, area);
    }

    return 0;
}

