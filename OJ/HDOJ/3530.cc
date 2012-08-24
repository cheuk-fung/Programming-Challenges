/*
 *  SRC: HDOJ 3530
 * PROB: Subsequence
 * ALGO: Monotone Priority Queue
 * DATE: Aug 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MAXN = 100010;

inline int MAX(int x, int y) { return x > y ? x : y; }

struct Node {
    int v, t;
    int id;
};
Node mxque[MAXN], mnque[MAXN];

int main()
{
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        int ans = 0;
        int mxhead = 0, mxtail = 0;
        int mnhead = 0, mntail = 0;
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);

            int mxpt = -1;
            while (mxhead < mxtail && mxque[mxtail - 1].v <= a) mxpt = mxque[--mxtail].t;
            mxque[mxtail++] = (Node){a, mxpt == -1 ? i : mxpt, i};

            int mnpt = -1;
            while (mnhead < mntail && mnque[mntail - 1].v >= a) mnpt = mnque[--mntail].t;
            mnque[mntail++] = (Node){a, mnpt == -1 ? i : mnpt, i};

            while (mxhead < mxtail && mnhead < mntail && mxque[mxhead].v - mnque[mnhead].v > k) {
                if (mxque[mxhead].id <= mnque[mnhead].id) mxhead++;
                else mnhead++;
            }

            if (mxhead < mxtail && mnhead < mntail && m <= mxque[mxhead].v - mnque[mnhead].v) {
                ans = MAX(ans, i - MAX(mxque[mxhead].t, mnque[mnhead].t) + 1);
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

