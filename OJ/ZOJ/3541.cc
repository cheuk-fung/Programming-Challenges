/*
 *  SRC: ZOJ 3541
 * PROB: The Last Puzzle
 * ALGO: DP
 * DATE: Sep 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MAXN = 209;
const int INF = 0x3f3f3f3f;

int T[MAXN], D[MAXN];
int f[MAXN][MAXN][2], next[MAXN][MAXN][2];

int dp(int l, int r, int dir)
{
    if (f[l][r][dir] != -1) return f[l][r][dir];
    if (l == r) return f[l][r][dir] = 0;

    f[l][r][dir] = INF;
    int ret = dp(l + 1, r, 0) + D[l + 1] - D[l];
    int add = 0;
    if (dir == 1) add = D[r] - D[l];
    if (ret < T[l] && ret + add < f[l][r][dir]) {
        f[l][r][dir] = ret + add;
        next[l][r][dir] = 0;
    }
    ret = dp(l, r - 1, 1) + D[r] - D[r - 1];
    add = 0;
    if (dir == 0) add = D[r] - D[l];
    if (ret < T[r] && ret + add < f[l][r][dir]) {
        f[l][r][dir] = ret + add;
        next[l][r][dir] = 1;
    }

    return f[l][r][dir];
}

void dump(int l, int r, int dir)
{
    if (l == r) {
        printf("%d\n", l + 1);
    } else if (next[l][r][dir] == 0) {
        printf("%d ", l + 1);
        dump(l + 1, r, 0);
    } else {
        printf("%d ", r + 1);
        dump(l, r - 1, 1);
    }
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        memset(f, 0xff, sizeof f);
        for (int i = 0; i < n; i++) scanf("%d", T + i);
        for (int i = 0; i < n; i++) scanf("%d", D + i);

        if (dp(0, n - 1, 0) == INF) {
            puts("Mission Impossible");
        } else {
            dump(0, n - 1, 0);
        }
    }

    return 0;
}

