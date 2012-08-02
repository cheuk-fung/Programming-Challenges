/*
 *  SRC: POJ 3216
 * PROB: Repairing Company
 * ALGO: Hungarian
 * DATE: Aug 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int mat[30][30];
int G[250][250];
int p[250], t[250], d[250];

int match[250], vis[250];

bool findpath(int u, int n)
{
    for (int v = 0; v < n; v++) {
        if (G[u][v] && !vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || findpath(match[v], n)) {
                match[v] = u;
                return true;
            }
        }
    }

    return false;
}

int hungarian(int n)
{
    int res = 0;
    memset(match, 0xff, sizeof match);
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof vis);
        if (findpath(i, n)) res++;
    }
    return res;
}

int main()
{
    int q, m;
    while (scanf("%d%d", &q, &m), q || m) {
        for (int i = 0; i < q; i++) {
            for (int j = 0; j < q; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", p + i, t + i, d + i);
            p[i]--;
        }

        for (int k = 0; k < q; k++) {
            for (int i = 0; i < q; i++) {
                for (int j = 0; j < q; j++) {
                    if (mat[i][k] >= 0 && mat[k][j] >= 0) {
                        if (mat[i][j] < 0) mat[i][j] = mat[i][k] + mat[k][j];
                        else mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                    }
                }
            }
        }

        memset(G, 0, sizeof G);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (i == j) continue;
                if (mat[p[i]][p[j]] >= 0 && t[i] + d[i] + mat[p[i]][p[j]] <= t[j]) {
                    G[i][j] = 1;
                }
            }
        }

        int r = hungarian(m);
        printf("%d\n", m - r);
    }

    return 0;
}

