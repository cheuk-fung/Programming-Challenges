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

int a[MAXN];
int mxque[MAXN], mnque[MAXN];

int main()
{
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        int ans = 0;
        int mxhead = 0, mxtail = 0;
        int mnhead = 0, mntail = 0;
        int left = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);

            while (mxhead < mxtail && a[mxque[mxtail - 1]] <= a[i]) mxtail--;
            mxque[mxtail++] = i;
            while (mnhead < mntail && a[mnque[mntail - 1]] >= a[i]) mntail--;
            mnque[mntail++] = i;
            while (mxhead < mxtail && mnhead < mntail && a[mxque[mxhead]] - a[mnque[mnhead]] > k) {
                if (mxque[mxhead] <= mnque[mnhead]) left = mxque[mxhead++] + 1;
                else left = mnque[mnhead++] + 1;
            }

            if (mxhead < mxtail && mnhead < mntail && m <= a[mxque[mxhead]] - a[mnque[mnhead]]) {
                ans = MAX(ans, i - left + 1);
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

