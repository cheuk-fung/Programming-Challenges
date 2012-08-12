/*
 *  SRC: HDOJ 1828
 * PROB: Picture
 * ALGO: Segment tree
 * DATE: Aug 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20010;
const int EPS = 10000;

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
                push_up(a, b, idx);
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));
            push_up(a, b, idx);
        }

        int query() { return val[1]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Segment {
    int x;
    int l, r, v;

    bool operator<(const Segment &o) const { return x == o.x ? v > o.v : x < o.x; }
} seg[MAXN];

int run(Segment *first, Segment *last, int st_size)
{
    sort(first, last);
    st.build(0, st_size);

    int res = 0;
    for (int prev = 0; first != last; first++) {
        st.update(first->l, first->r, first->v);
        int r = st.query();
        res += abs(r - prev);
        prev = r;
    }

    return res;
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int xmx = 0, ymx = 0;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 += EPS; y1 += EPS; x2 += EPS; y2 += EPS;
            seg[i * 2] = (Segment){x1, y1, y2, 1};
            seg[i * 2 + 1] = (Segment){x2, y1, y2, -1};
            seg[i * 2 + 2 * n] = (Segment){y1, x1, x2, 1};
            seg[i * 2 + 2 * n + 1] = (Segment){y2, x1, x2, -1};
            xmx = max(xmx, x2);
            ymx = max(ymx, y2);
        }
        printf("%d\n", run(seg, seg + 2 * n, ymx + 1) + run(seg + 2 * n, seg + 4 * n, xmx + 1));
    }

    return 0;
}

