/*
 *  SRC: POJ 1390
 * PROB: Blocks
 * ALGO: DP
 * DATE: Oct 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int block[209];
int color[209], cnt[209];
int f[209][209][209];

inline int SQR(int x) { return x * x; }

int dp(int l, int r, int k)
{
    if (f[l][r][k] != -1) return f[l][r][k];
    if (l == r) return f[l][r][k] = SQR(cnt[l] + k);

    int res = dp(l, r - 1, 0) + SQR(cnt[r] + k);
    assert(color[r - 1] != color[r]);
    for (int i = l; i < r; i++) {
        if (color[i] == color[r]) {
            res = max(res, dp(l, i, cnt[r] + k) + dp(i + 1, r - 1, 0));
        }
    }

    return f[l][r][k] = res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", block + i);
        }

        int m = 0;
        color[m] = block[0];
        cnt[m] = 1;
        for (int i = 1; i < n; i++) {
            if (color[m] == block[i]) {
                cnt[m]++;
            } else {
                color[++m] = block[i];
                cnt[m] = 1;
            }
        }
        m++;

        memset(f, 0xff, sizeof f);
        printf("Case %d: %d\n", task, dp(0, m - 1, 0));
    }

    return 0;
}

