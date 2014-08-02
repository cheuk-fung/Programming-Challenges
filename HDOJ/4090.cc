/*
 *  SRC: HDOJ 4090
 * PROB: Gem And Prince
 * ALGO: DFS
 * DATE: Sep 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int dir[8][2] = {
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1}
};

int n, m, k, ans;
int mat[30][10][10];
int Q[30][100], vis[30][10][10];
int rest[10];

inline int count_rest()
{
    int r = 0;
    for (int i = 1; i <= k; i++) {
        r += rest[i] * rest[i];
    }
    return r;
}

void dfs(int depth, int now)
{
    if (now + count_rest() <= ans) return ;
    if (now > ans) ans = now;

    memset(vis[depth], 0, sizeof vis[depth]);
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (vis[depth][i][j] || mat[depth][i][j] == 0) continue;

            int *head = Q[depth], *tail = Q[depth];
            *tail++ = i << 4 | j;
            vis[depth][i][j] = true;
            while (head != tail) {
                int u = *head++;
                int x = u >> 4, y = u & 0xf;
                for (int d = 0; d < 8; d++) {
                    int xx = x + dir[d][0];
                    int yy = y + dir[d][1];
                    if (!vis[depth][xx][yy] && mat[depth][xx][yy] == mat[depth][x][y]) {
                        vis[depth][xx][yy] = true;
                        *tail++ = xx << 4 | yy;
                    }
                }
            }

            int cnt = tail - Q[depth];
            int col = mat[depth][i][j];
            if (cnt >= 3) {
                memcpy(mat[depth + 1], mat[depth], sizeof mat[depth]);
                for (int *head = Q[depth]; head != tail; head++) {
                    int x = *head >> 4, y = *head & 0xf;
                    mat[depth + 1][x][y] = 0;
                }

                for (int j = 1; j <= m; j++) {
                    int k = n;
                    while (k >= 1 && mat[depth + 1][k][j] != 0) k--;
                    for (int i = k; k >= 1; i--, k--) {
                        while (k >= 1 && mat[depth + 1][k][j] == 0) k--;
                        if (k >= 1) {
                            mat[depth + 1][i][j] = mat[depth + 1][k][j];
                            mat[depth + 1][k][j] = 0;
                        }
                    }
                }

                int k = 1;
                while (k <= m && mat[depth + 1][n][k] != 0) k++;
                for (int j = k; k <= m; j++, k++) {
                    while (k <= m && mat[depth + 1][n][k] == 0) k++;
                    if (k <= m) {
                        for (int i = 1; i <= n; i++) {
                            mat[depth + 1][i][j] = mat[depth + 1][i][k];
                            mat[depth + 1][i][k] = 0;
                        }
                    }
                }

                rest[col] -= cnt;
                dfs(depth + 1, now + cnt * cnt);
                rest[col] += cnt;
            }
        }
    }
}

int main()
{
    while (~scanf("%d%d%d", &n, &m, &k)) {
        memset(mat[0], 0, sizeof mat[0]);
        memset(rest, 0, sizeof rest);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &mat[0][i][j]);
                rest[mat[0][i][j]]++;
            }
        }

        ans = 0;
        dfs(0, 0);
        printf("%d\n", ans);
    }

    return 0;
}

