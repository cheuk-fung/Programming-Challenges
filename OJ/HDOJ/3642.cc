/*
 *  SRC: HDOJ 3642
 * PROB: Get The Treasury
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
#include <utility>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 2048;

int n;
int ycnt, zcnt;
int yall[MAXN], zall[MAXN];

struct Spot {
    int x;
    int y1, y2;
    int z1, z2;
    int v;

    bool operator<(const Spot &o) const { return x < o.x; }
} spots[MAXN];

class Segment_tree {
    private:
        static int lep, rep;

        int cnt[MAXN << 2];
        int val[MAXN << 2][3];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int a, int b, int idx)
        {
            val[idx][0] = val[idx][1] = val[idx][2] = 0;

            if (a + 1 == b) {
                if (cnt[idx]) {
                    val[idx][cnt[idx] - 1] = yall[b] - yall[a];
                }
                return ;
            }

            if (cnt[idx] > 2) {
                val[idx][2] = yall[b] - yall[a];
            } else if (cnt[idx] > 1) {
                val[idx][2] = val[LC(idx)][0] + val[LC(idx)][1] + val[LC(idx)][2] + val[RC(idx)][0] + val[RC(idx)][1] + val[RC(idx)][2];
                val[idx][1] = yall[b] - yall[a] - val[idx][2];
            } else if (cnt[idx]) {
                val[idx][1] = val[LC(idx)][0] + val[RC(idx)][0];
                val[idx][2] = val[LC(idx)][1] + val[LC(idx)][2] + val[RC(idx)][1] + val[RC(idx)][2];
                val[idx][0] = yall[b] - yall[a] - val[idx][1] - val[idx][2];
            } else {
                val[idx][0] = val[LC(idx)][0] + val[RC(idx)][0];
                val[idx][1] = val[LC(idx)][1] + val[RC(idx)][1];
                val[idx][2] = val[LC(idx)][2] + val[RC(idx)][2];
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

        int query() { return val[1][2]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

long long calc(int z)
{
    st.build(0, MAXN);
    long long area = 0, len = 0;
    for (int i = 0, prevx = 0; i < 2 * n; i++) {
        if (spots[i].z1 <= z && z < spots[i].z2) {
            area += len * (spots[i].x - prevx);
            prevx = spots[i].x;

            st.update(spots[i].y1, spots[i].y2, spots[i].v);
            len = st.query();
        }
    }
    return area;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int x1, y1, z1, x2, y2, z2;
            scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
            spots[i << 1] = (Spot){x1, y1, y2, z1, z2, 1};
            spots[i << 1 | 1] = (Spot){x2, y1, y2, z1, z2, -1};
            yall[i << 1] = y1; yall[i << 1 | 1] = y2;
            zall[i << 1] = z1; zall[i << 1 | 1] = z2;
        }
        sort(spots, spots + 2 * n);
        sort(yall, yall + 2 * n);
        sort(zall, zall + 2 * n);
        ycnt = unique(yall, yall + 2 * n) - yall;
        zcnt = unique(zall, zall + 2 * n) - zall;

        for (int i = 0; i < 2 * n; i++) {
            spots[i].y1 = lower_bound(yall, yall + ycnt, spots[i].y1) - yall;
            spots[i].y2 = lower_bound(yall, yall + ycnt, spots[i].y2) - yall;
        }

        long long volume = 0, area = 0;
        for (int i = 0; i < zcnt; i++) {
            if (i > 0) volume += area * (zall[i] - zall[i - 1]);
            area = calc(zall[i]);
        }
        cout << "Case " << task << ": " << volume << endl;
    }

    return 0;
}

