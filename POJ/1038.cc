/*
 *  SRC: POJ 1038
 * PROB: Bugs Integrated, Inc.
 * ALGO: DP
 * DATE: Aug 30, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::max;

int n, m, k, final;
int map[151], f[2][1024][1024];
int curr = 0, next = 1;

void dfs(int l1, int l2, int l3, int m1, int m2, int m3, int cnt)
{
    f[next][l2][l3] = max(f[next][l2][l3], cnt);

    int can_put = l1 | l2 | m1 | m2;
    for (int i = 7; i < final; i <<= 1)
        if (!(can_put & i)) dfs(l1 | i, l2 | i, l3, m1, m2, m3, cnt + 1);

    can_put |= l3 | m3;
    for (int i = 3; i < final; i <<= 1)
        if (!(can_put & i)) dfs(l1 | i, l2 | i, l3 | i, m1, m2, m3, cnt + 1);
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        memset(map, 0, sizeof(map));
        memset(f, 0xff, sizeof(f));

        scanf("%d%d%d", &n, &m, &k);
        final = 1 << m;

        for (int i = 0; i < k; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            map[x - 1] |= 1 << (y - 1);
        }

        f[curr][0][0] = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < final; j++) {
                if (j & map[i]) continue;
                for (int k = 0; k < final; k++) {
                    if (k & map[i + 1]) continue;
                    if (f[curr][j][k] < 0) continue;
                    dfs(j, k, 0, map[i], map[i + 1], map[i + 2], f[curr][j][k]);
                }
            }
            memset(f[curr], 0xff, sizeof(f[curr]));
            curr ^= 1;
            next ^= 1;
        }

        int ans = 0;
        for (int i = 0; i < final; i++) ans = max(ans, f[curr][i][0]);
        printf("%d\n", ans);
    }

    return 0;
}
