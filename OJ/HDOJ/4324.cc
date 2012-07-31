/*
 *  SRC: HDOJ 4324
 * PROB: Triangle LOVE
 * ALGO: DFS
 * DATE: Jul 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAXN = 2222;

int n;
bool vis[MAXN];
char mat[MAXN][MAXN];

bool dfs(int x, int fa, int pa)
{
    vis[x] = true;
    for (int i = 0; i < n; i++) {
        if (i == pa && mat[x][i] == '1') return true;
        if (!vis[i] && mat[x][i] == '1') {
            if (dfs(i, x, fa)) return true;
        }
    }

    return false;
}

bool exist()
{
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; i++) {
        if (!vis[i] && dfs(i, -1, -1)) {
            return true;
        }
    }
    return false;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++)  {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", mat[i]);
        }

        printf("Case #%d: %s\n", task, exist() ? "Yes" : "No");
    }

    return 0;
}
