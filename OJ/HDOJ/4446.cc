/*
 *  SRC: HDOJ 4446
 * PROB: IT Companies
 * ALGO: Segment Tree
 * DATE: Oct 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 100010;

class Segment_tree {
    private:
        static int lep, rep;

        int mn[MAXN << 3], mnid[MAXN << 3];
        int offset[MAXN << 3];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void pushup(int x)
        {
            assert(offset[x] == 0);
            if (mn[LC(x)] + offset[LC(x)] <= mn[RC(x)] + offset[RC(x)]) {
                mn[x] = mn[LC(x)] + offset[LC(x)];
                mnid[x] = mnid[LC(x)];
            } else {
                mn[x] = mn[RC(x)] + offset[RC(x)];
                mnid[x] = mnid[RC(x)];
            }
        }

        void pushdown(int x)
        {
            offset[LC(x)] += offset[x];
            offset[RC(x)] += offset[x];
            offset[x] = 0;
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(mn, 0, sizeof mn);
            memset(offset, 0, sizeof offset);
        }

        void update(int c, int d, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                offset[idx] += v;
                if (a + 1 == b) {
                    mnid[idx] = a;
                }
                return ;
            }

            pushdown(idx);

            int mid = (a + b) >> 1;
            if (c < mid) update(c, d, v, a, mid, LC(idx));
            if (d > mid) update(c, d, v, mid, b, RC(idx));

            pushup(idx);
        }

        int query() const
        {
            if (mn[1] + offset[1] == 0) return mnid[1];
            return -1;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

int ans[MAXN << 1];
queue<int> negtive;

void work(int n)
{
    int top = 0;
    for (int i = 0; i < n; i++) {
        int x;
        while ((x = st.query()) == -1) {
            if (negtive.empty()) {
                puts("Impossible");
                return ;
            }
            int now = negtive.front();
            negtive.pop();
            ans[top++] = -now;
            if (now < n) {
                st.update(now + 1, n + 1, -1);
            }
        }
        ans[top++] = x;
        negtive.push(x);
        if (x > 1) {
            st.update(1, x, -1);
        }
        st.update(x, x + 1, MAXN);
    }
    while (!negtive.empty()) {
        ans[top++] = -negtive.front();
        negtive.pop();
    }
    for (int i = top - 1; i >= 0; i--) {
        printf("%d ", ans[i]);
    }
    putchar(10);
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        st.build(1, n + 1);
        for (int i = 1; i <= n; i++) {
            int c;
            scanf("%d", &c);
            st.update(i, i + 1, c);
        }
        work(n);
    }

    return 0;
}

