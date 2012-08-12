/*
 *  SRC: HDOJ 4351
 * PROB: Digital root
 * ALGO: Segment tree
 * DATE: Aug 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

const int MAXN = 100010;
int val[MAXN], vis[10], f[1 << 10][1 << 10];

struct Tnode {
    int s, l, r;
    int all;

    void set(int u, int v)
    {
        s = l = r = u;
        all = v;
    }
};

inline int calc(int v)
{
    if (!v) return v;

    v %= 9;
    return v ? v : 9;
}

class Segment_tree {
    private:
        static int lep, rep;
        Tnode node[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(Tnode &a, const Tnode &b, const Tnode &c)
        {
            if (b.all == -1) a = c;
            else if (c.all == -1) a = b;
            else {
                a.all = calc(b.all + c.all);
                a.l = b.l;
                a.l |= f[1 << b.all][c.l];
                a.r = c.r;
                a.r |= f[1 << c.all][b.r];
                a.s = b.s | c.s | a.l | a.r | f[b.r][c.l];
            }
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
        }

        void update(int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                node[idx].set(1 << val[a], val[a]);
                return ;
            }

            int mid = (a + b) >> 1;
            update(a, mid, LC(idx));
            update(mid, b, RC(idx));
            push_up(node[idx], node[LC(idx)], node[RC(idx)]);
        }

        Tnode query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return node[idx];
            }

            Tnode res, l, r;
            res.set(0, -1);
            l.set(0, -1);
            r.set(0, -1);

            int mid = (a + b) >> 1;
            if (c < mid) l = query(c, d, a, mid, LC(idx));
            if (d > mid) r = query(c, d, mid, b, RC(idx));
            push_up(res, l, r);
            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int main()
{
    for (int i = 1; i < 1 << 10; i++) {
        for (int j = 1; j < 1 << 10; j++) {
            int first = 9;
            while ((i >> first) == 0) first--;
            f[i][j] = f[i ^ (1 << first)][j];
            for (int k = 0; k < 10; k++) {
                if ((j >> k) & 1) {
                    f[i][j] |= 1 << calc(first + k);
                }
            }
        }
    }

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case #%d:\n", task);

        int n;
        scanf("%d", &n);
        st.build(0, n);
        for (int i = 0; i < n; i++) {
            scanf("%d", val + i);
            val[i] = calc(val[i]);
        }
        st.update();

        int q;
        scanf("%d", &q);
        while (q--) {
            int l, r;
            scanf("%d%d", &l, &r);
            Tnode res = st.query(l - 1, r);
            int cnt = 0;
            int bit = 9;
            while (bit >= 0) {
                if ((res.s >> bit) & 1) {
                    printf("%d", bit);
                    cnt++;
                    if (cnt < 5) putchar(' ');
                    else {
                        putchar(10);
                        break;
                    }
                }
                bit--;
            }
            while (cnt < 5) {
                printf("-1");
                cnt++;
                if (cnt < 5) putchar(' ');
                else putchar(10);
            }
        }

        if (task != tasks) putchar(10);
    }

    return 0;
}

