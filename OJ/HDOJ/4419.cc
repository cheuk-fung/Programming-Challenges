/*
 *  SRC: HDOJ 4419
 * PROB: Colourful Rectangle
 * ALGO: Segment tree
 * DATE: Sep 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10010;

int ycnt;
long long yall[MAXN << 1];

class Segment_tree {
    private:
        static int lep, rep;

        struct Tnode {
            int cover;
            long long length;
        } node[MAXN << 3];

        int LC(int x) const { return x << 1; }
        int RC(int x) const { return x << 1 | 1; }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(node, 0, sizeof node);
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                node[idx].cover += v;
            } else {
                int mid = (a + b) >> 1;
                if (c < mid) update(c, d, v, a, mid, LC(idx));
                if (d > mid) update(c, d, v, mid, b, RC(idx));
            }

            if (node[idx].cover) {
                node[idx].length = yall[b] - yall[a];
            } else if (a + 1 < b) {
                node[idx].length = node[LC(idx)].length + node[RC(idx)].length;
            } else {
                node[idx].length = 0;
            }
        }

        long long query() const { return node[1].length; }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Rectangle {
    int x1, y1, x2, y2, col;
} rect[MAXN];

struct Segment {
    int x;
    int l, r, c, v;

    bool operator<(const Segment &o) const { return x < o.x; }
} seg[MAXN << 1];
int segcnt;
bool avail[3];

long long area(bool R, bool G, bool B)
{
    avail[0] = R;
    avail[1] = G;
    avail[2] = B;

    long long r = 0;
    st.build(0, ycnt);
    for (int i = 0, prev = -1; i < segcnt; i++) {
        if (!avail[seg[i].c]) continue;
        if (prev != -1) {
            r += st.query() * (seg[i].x - prev);
        }
        st.update(seg[i].l, seg[i].r, seg[i].v);
        prev = seg[i].x;
    }
    return r;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);

        ycnt = 0;
        for (int i = 0; i < n; i++) {
            char col;
            int x1, y1, x2, y2, c;
            scanf(" %c%d%d%d%d", &col, &x1, &y1, &x2, &y2);
            if (col == 'R') c = 0;
            else if (col == 'G') c = 1;
            else c = 2;
            rect[i] = (Rectangle){x1, y1, x2, y2, c};
            yall[ycnt++] = y1;
            yall[ycnt++] = y2;
        }
        sort(yall, yall + ycnt);
        ycnt = unique(yall, yall + ycnt) - yall;

        segcnt = 0;
        for (int i = 0; i < n; i++) {
            int y1 = lower_bound(yall, yall + ycnt, rect[i].y1) - yall;
            int y2 = lower_bound(yall, yall + ycnt, rect[i].y2) - yall;
            seg[segcnt++] = (Segment){rect[i].x1, y1, y2, rect[i].col, 1};
            seg[segcnt++] = (Segment){rect[i].x2, y1, y2, rect[i].col, -1};
        }
        sort(seg, seg + segcnt);

        long long tR = area(1, 0, 0);
        long long tG = area(0, 1, 0);
        long long tB = area(0, 0, 1);
        long long tRG = area(1, 1, 0);
        long long tRB = area(1, 0, 1);
        long long tGB = area(0, 1, 1);
        long long tRGB = area(1, 1, 1);

        long long R = tRGB - tGB;
        long long G = tRGB - tRB;
        long long B = tRGB - tRG;
        long long RGB = tR + tG + tB - tRG - tRB - tGB + tRGB;
        long long RG = tR + tG - tRG - RGB;
        long long RB = tR + tB - tRB - RGB;
        long long GB = tG + tB - tGB - RGB;

        printf("Case %d:\n", task);
        printf("%I64d\n", R);
        printf("%I64d\n", G);
        printf("%I64d\n", B);
        printf("%I64d\n", RG);
        printf("%I64d\n", RB);
        printf("%I64d\n", GB);
        printf("%I64d\n", RGB);
    }

    return 0;
}

