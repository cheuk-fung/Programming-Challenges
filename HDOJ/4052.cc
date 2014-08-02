/*
 *  SRC: HDOJ 4052
 * PROB: Adding New Machine
 * ALGO: Segment tree
 * DATE: Aug 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

int w, h, n, m;
int ycnt, yall[MAXN << 4];

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int l, r;
            long long cnt;
        } node[MAXN << 4];

        int LC(int x) const { return x << 1; }
        int RC(int x) const { return x << 1 | 1; }
        long long count(int a, int b) const
        {
            if (yall[b] - yall[a] >= m) {
                return yall[b] - yall[a] - m + 1;
            }
            return 0;
        }

        void push_up(int a, int b, int idx)
        {
            int mid = (a + b) >> 1;
            node[idx].l = node[LC(idx)].l;
            if (node[LC(idx)].l == mid - a) node[idx].l += node[RC(idx)].l;
            node[idx].r = node[RC(idx)].r;
            if (node[RC(idx)].r == b - mid) node[idx].r += node[LC(idx)].r;
            node[idx].cnt = node[LC(idx)].cnt + node[RC(idx)].cnt;
            if (node[LC(idx)].l != mid - a && node[RC(idx)].r != b - mid) {
                // printf("!!!! %d %d %d %lld\n", m, yall[mid - node[LC(idx)].r], yall[mid + node[RC(idx)].l], node[idx].cnt);
                node[idx].cnt += count(mid - node[LC(idx)].r, mid + node[RC(idx)].l);
                // printf("!!!! %d %d %d %lld\n", m, yall[mid - node[LC(idx)].r], yall[mid + node[RC(idx)].l], node[idx].cnt);
            }
            while (node[idx].l == b - a && node[idx].cnt != 0) ;
        }

        void push_down(int a, int b, int idx)
        {
            if (node[idx].l == b - a) {
                while (node[idx].cnt != 0) ;
                int mid = (a + b) >> 1;
                node[LC(idx)].l = node[LC(idx)].r = mid - a;
                node[LC(idx)].cnt = 0;
                node[RC(idx)].l = node[RC(idx)].r = b - mid;
                node[RC(idx)].cnt = 0;
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
                if (v) {
                    node[idx].l = node[idx].r = b - a;
                    node[idx].cnt = 0;
                } else {
                    node[idx].l = node[idx].r = node[idx].cnt = 0;
                }
                return ;
            }

            push_down(a, b, idx);
            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));
            push_up(a, b, idx);
        }

        long long query() const
        {
            long long res = node[1].cnt + count(lep, lep + node[1].l);
            if (node[1].l != rep - lep) res += count(rep - node[1].r, rep);
            return res;
        }

} st;
int Segment_tree::lep, Segment_tree::rep;

struct Rectangle {
    int x1, y1, x2, y2;
} rect[MAXN];

struct Segment {
    int x;
    int l, r;
    int v;

    bool operator<(const Segment &o) const { return x == o.x ? v > o.v : x < o.x; }
} seg[MAXN << 4];
int scnt;

long long run()
{
    long long res = 0, now = 0;
    st.build(0, ycnt - 1);
    for (int i = 0; i < scnt; i++) {
        if (i > 0) res += now * (seg[i].x - seg[i - 1].x);
        st.update(seg[i].l, seg[i].r, seg[i].v);
        now = st.query();
    }

    return res;
}

int main()
{
    // printf("%d\n", (sizeof st + sizeof rect + sizeof seg + sizeof yall) / 1024);
    while (~scanf("%d%d%d%d", &w, &h, &n, &m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
        }

        ycnt = 0;
        yall[ycnt++] = 1;
        yall[ycnt++] = h + 1;
        for (int i = 0; i < n; i++) {
            yall[ycnt++] = rect[i].y1;
            yall[ycnt++] = rect[i].y2 + 1;
        }
        sort(yall, yall + ycnt);
        ycnt = unique(yall, yall + ycnt) - yall;

        scnt = 0;
        seg[scnt++] = (Segment){1, 0, ycnt - 1, 1};
        seg[scnt++] = (Segment){w + 1, 0, ycnt - 1, 0};
        for (int i = 0; i < n; i++) {
            int y1 = lower_bound(yall, yall + ycnt, rect[i].y1) - yall;
            int y2 = lower_bound(yall, yall + ycnt, rect[i].y2 + 1) - yall;
            seg[scnt++] = (Segment){rect[i].x1, y1, y2, 0};
            seg[scnt++] = (Segment){rect[i].x2 + 1, y1, y2, 1};
        }
        sort(seg, seg + scnt);

        long long ans = run();
        // printf("\n%lld\n", ans);
        if (m != 1) {
            ycnt = 0;
            yall[ycnt++] = 1;
            yall[ycnt++] = w + 1;
            for (int i = 0; i < n; i++) {
                yall[ycnt++] = rect[i].x1;
                yall[ycnt++] = rect[i].x2 + 1;
            }
            sort(yall, yall + ycnt);
            ycnt = unique(yall, yall + ycnt) - yall;

            scnt = 0;
            seg[scnt++] = (Segment){1, 0, ycnt - 1, 1};
            seg[scnt++] = (Segment){h + 1, 0, ycnt - 1, 0};
            for (int i = 0; i < n; i++) {
                int x1 = lower_bound(yall, yall + ycnt, rect[i].x1) - yall;
                int x2 = lower_bound(yall, yall + ycnt, rect[i].x2 + 1) - yall;
                seg[scnt++] = (Segment){rect[i].y1, x1, x2, 0};
                seg[scnt++] = (Segment){rect[i].y2 + 1, x1, x2, 1};
            }
            sort(seg, seg + scnt);

            ans += run();
        }

        // printf("%lld\n", ans);
        printf("%I64d\n", ans);
    }

    return 0;
}

