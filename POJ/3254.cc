/*
 *  SRC: POJ 3254
 * PROB: Corn Fields
 * ALGO: DP
 * DATE: Aug 31, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MOD = 100000000;

int n, m, final;
int map[12], f[2][1 << 12];
int curr = 0, next = 1;

void dfs(int r, int c, int status, int new_status)
{
    if (c >= m) {
        f[next][new_status] = (f[curr][status] + f[next][new_status]) % MOD;
        return ;
    }

    if ((map[r] & (1 << c)) && !(status & (1 << c)))
        dfs(r, c + 2, status, new_status | (1 << c));

    dfs(r, c + 1, status, new_status);
}

int main()
{
    scanf("%d%d", &n, &m);
    final = 1 << m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int t;
            scanf("%d", &t);
            map[i] <<= 1;
            if (t) map[i]++;
        }

    f[curr][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < final; j++)
            if (f[curr][j]) dfs(i, 0, j, 0);
        memset(f[curr], 0, sizeof(f[curr]));
        curr ^= 1;
        next ^= 1;
    }

    int ans = 0;
    for (int i = 0; i < final; i++) ans = (ans + f[curr][i]) % MOD;
    printf("%d\n", ans);

    return 0;
}
