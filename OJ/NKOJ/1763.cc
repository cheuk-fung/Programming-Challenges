/*
 *  SRC: NKOJ 1763
 * PROB: Optimal Milking
 * ALGO: Hungarian
 * DATE: Jul 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int K, C, M;
int mat[250][250];
int G[250][50];
int match[50][20];
int vis[50];

bool find_path(int u)
{
    for (int v = 0; v < K; v++) {
        if (G[u][v] && !vis[v]) {
            vis[v] = true;
            for (int i = 0; i < M; i++) {
                if (match[v][i] == -1 || find_path(match[v][i])) {
                    match[v][i] = u;
                    return true;
                }
            }
        }
    }
    return false;
}

bool check(int x)
{
    memset(G, 0, sizeof G);
    for (int i = K; i < K + C; i++) {
        for (int j = 0; j < K; j++) {
            if (mat[i][j] && mat[i][j] <= x) {
                G[i - K][j] = 1;
            }
        }
    }

    int cnt = 0;
    memset(match, 0xff, sizeof match);
    for (int i = 0; i < C; i++) {
        memset(vis, 0, sizeof vis);
        if (find_path(i)) cnt++;
    }

    return cnt == C;
}

int main()
{
    scanf("%d%d%d", &K, &C, &M);
    for (int i = 0; i < K + C; i++) {
        for (int j = 0; j < K + C; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    for (int k = 0; k < K + C; k++) {
        for (int i = 0; i < K + C; i++) {
            for (int j = 0; j < K + C; j++) {
                if (mat[i][k] && mat[k][j]) {
                    if (!mat[i][j]) mat[i][j] = mat[i][k] + mat[k][j];
                    else mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }
    }

    int l = 0, r = 0;
    for (int i = 0; i < K + C; i++) {
        for (int j = 0; j < K + C; j++) {
            r = max(r, mat[i][j]);
        }
    }
    while (l < r) {
        int mid = (l + r - 1) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%d\n", l);

    return 0;
}

