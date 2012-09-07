/*
 *  SRC: HDOJ 4007
 * PROB: Dave
 * ALGO: Segment tree
 * DATE: Sep 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return x << 1 | 1; }

class Segment_tree {
    private:
        static int lep, rep;
        int val[2020 << 2];
        int mxv[2020 << 2];

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(val, 0, sizeof val);
            memset(mxv, 0, sizeof mxv);
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                val[idx] += v;
            } else {
                int mid = (a + b) >> 1;
                if (c < mid) update(c, d, v, a, mid, LC(idx));
                if (d > mid) update(c, d, v, mid, b, RC(idx));
            }
            mxv[idx] = val[idx];
            if (a + 1 != b) mxv[idx] += max(mxv[LC(idx)], mxv[RC(idx)]);
        }

        int query() const { return mxv[1]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

pair<long long, long long> peo[1010];

long long yall[2020];
int ycnt;

struct Segment {
    long long x;
    int y1, y2;
    int v;

    bool operator<(const Segment &o) const { return x == o.x ? v > o.v : x < o.x; }
} seg[2020];
int scnt;

int main()
{
    int n, r;
    while (~scanf("%d%d", &n, &r)) {
        ycnt = 0;
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            peo[i] = make_pair(x << 1ll, y << 1ll);
            yall[ycnt++] = peo[i].second - r;
            yall[ycnt++] = peo[i].second + r;
        }
        sort(yall, yall + ycnt);
        ycnt = unique(yall, yall + ycnt) - yall;

        scnt = 0;
        for (int i = 0; i < n; i++) {
            int y1 = lower_bound(yall, yall + ycnt, peo[i].second - r) - yall;
            int y2 = lower_bound(yall, yall + ycnt, peo[i].second + r) - yall;
            seg[scnt++] = (Segment){peo[i].first - r, y1, y2, 1};
            seg[scnt++] = (Segment){peo[i].first + r, y1, y2, -1};
        }
        sort(seg, seg + scnt);

        st.build(0, ycnt);
        int ans = 0;
        for (int i = 0; i < scnt; i++) {
            st.update(seg[i].y1, seg[i].y2 + 1, seg[i].v);
            ans = max(ans, st.query());
        }
        printf("%d\n", ans);
    }

    return 0;
}

