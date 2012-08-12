/*
 *  SRC: HDOJ 3265
 * PROB: Posters
 * ALGO: Segment tree
 * DATE: Aug 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        int cnt[MAXN << 2];
        int val[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            if (cnt[idx]) {
                val[idx] = b - a;
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
            memset(cnt, 0, sizeof cnt);
            memset(val, 0, sizeof val);
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                cnt[idx] += v;
            } else {
                int mid = (a + b) >> 1;
                if (c < mid) update(c, d, v, a, mid, LC(idx));
                if (d > mid) update(c, d, v, mid, b, RC(idx));
            }
            push_up(a, b, idx);
        }

        int query() { return val[1]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Segment {
    int x;
    int l, r;
    int v;

    bool operator<(const Segment &o) const { return x < o.x; }
} seg[MAXN << 3];

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        int idx = 0;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2, x3, y3, x4, y4;
            scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            seg[idx++] = (Segment){x1, y1, y2, 1};
            seg[idx++] = (Segment){x3, y1, y2, -1};
            seg[idx++] = (Segment){x3, y1, y3, 1};
            seg[idx++] = (Segment){x4, y1, y3, -1};
            seg[idx++] = (Segment){x3, y4, y2, 1};
            seg[idx++] = (Segment){x4, y4, y2, -1};
            seg[idx++] = (Segment){x4, y1, y2, 1};
            seg[idx++] = (Segment){x2, y1, y2, -1};
        }
        sort(seg, seg + idx);
        st.build(0, MAXN);

        long long area = 0;
        for (int i = 0; i < idx; i++) {
            long long r = st.query();
            if (i > 0) area += (seg[i].x - seg[i - 1].x) * r;
            st.update(seg[i].l, seg[i].r, seg[i].v);
        }

        cout << area << endl;
    }

    return 0;
}

