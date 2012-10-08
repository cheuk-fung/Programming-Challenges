/*
 *  SRC: ZOJ 1234
 * PROB: Chopsticks
 * ALGO: DP
 * DATE: Oct 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int l[5010];
int f[5010][1010];

inline int SQR(int x) { return x * x; }

int dp(int x, int k, int n)
{
    if (k == 0) return 0;
    if (x >= n) return INF;
    if (k * 3 > n - x) return INF;
    if (f[x][k] != -1) return f[x][k];
    return f[x][k] = min(dp(x + 1, k, n), dp(x + 2, k - 1, n) + SQR(l[x] - l[x + 1]));
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int k, n;
        scanf("%d%d", &k, &n);
        for (int i = 0; i < n; i++) scanf("%d", l + i);

        memset(f, 0xff, sizeof f);
        int r = dp(0, k + 8, n);
        printf("%d\n", r);
    }

    return 0;
}

