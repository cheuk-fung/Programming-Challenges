/*
 *  SRC: HDOJ 3255
 * PROB: Farming
 * ALGO: Segment tree
 * DATE: Aug 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 60010;

struct Vegetable {
    int price, kind;
    bool operator<(const Vegetable &o) const { return price < o.price; }
} veg[3];
int nkind[3];

struct Segment {
    int x;
    int y1, y2;
    int s, v;
    bool operator<(const Segment &o) const { return x < o.x; }
} seg[MAXN];
int yall[MAXN], ycnt;

class Segment_tree {
    private:
        static int lep, rep;

        int cnt[MAXN << 2][3];
        int val[MAXN << 2][3];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            val[idx][0] = val[idx][1] = val[idx][2] = 0;
            if (a + 1 == b) {
                if (cnt[idx][2]) val[idx][2] = yall[b] - yall[a];
                else if (cnt[idx][1]) val[idx][1] = yall[b] - yall[a];
                else if (cnt[idx][0]) val[idx][0] = yall[b] - yall[a];
                return ;
            }

            if (cnt[idx][2]) {
                val[idx][2] = yall[b] - yall[a];
            } else if (cnt[idx][1]) {
                val[idx][2] = val[LC(idx)][2] + val[RC(idx)][2];
                val[idx][1] = yall[b] - yall[a] - val[idx][2];
            } else if (cnt[idx][0]) {
                val[idx][2] = val[LC(idx)][2] + val[RC(idx)][2];
                val[idx][1] = val[LC(idx)][1] + val[RC(idx)][1];
                val[idx][0] = yall[b] - yall[a] - val[idx][2] - val[idx][1];
            } else {
                val[idx][2] = val[LC(idx)][2] + val[RC(idx)][2];
                val[idx][1] = val[LC(idx)][1] + val[RC(idx)][1];
                val[idx][0] = val[LC(idx)][0] + val[RC(idx)][0];
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

        void update(int c, int d, int kind, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                cnt[idx][kind] += v;
            } else {
                int mid = (a + b) >> 1;
                if (c < mid) update(c, d, kind, v, a, mid, LC(idx));
                if (d > mid) update(c, d, kind, v, mid, b, RC(idx));
            }
            push_up(a, b, idx);
        }

        int query()
        {
            return val[1][0] * veg[0].price + val[1][1] * veg[1].price + val[1][2] * veg[2].price;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        memset(veg, 0, sizeof veg);

        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &veg[i].price);
            veg[i].kind = i;
        }
        sort(veg, veg + m);
        for (int i = 0; i < m; i++) {
            nkind[veg[i].kind] = i;
        }

        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2, s;
            scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &s);
            seg[i << 1] = (Segment){x1, y1, y2, s, 1};
            seg[i << 1 | 1] = (Segment){x2, y1, y2, s, -1};
            yall[i << 1] = y1;
            yall[i << 1 | 1]= y2;
        }
        sort(yall, yall + 2 * n);
        ycnt = unique(yall, yall + 2 * n) - yall;

        for (int i = 0; i < 2 * n; i++) {
            seg[i].y1 = lower_bound(yall, yall + ycnt, seg[i].y1) - yall;
            seg[i].y2 = lower_bound(yall, yall + ycnt, seg[i].y2) - yall;
        }
        sort(seg, seg + 2 * n);

        st.build(0, MAXN);
        long long len = 0, value = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (i > 0) value += len * (seg[i].x - seg[i - 1].x);
            st.update(seg[i].y1, seg[i].y2, nkind[seg[i].s - 1], seg[i].v);
            len = st.query();
        }

        cout << "Case " << task << ": " << value << endl;
    }

    return 0;
}

