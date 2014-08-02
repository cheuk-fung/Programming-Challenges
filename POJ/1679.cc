/*
 *  SRC: POJ 1679
 * PROB: The Unique MST
 * ALGO: MST
 * DATE: Jul 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 110;

int n, m;
int mst;
int mat[MAXN][MAXN];
int vis[MAXN][MAXN];
int dist[MAXN], parent[MAXN];

int find_edge(int u, int parent, int target)
{
    if (u == target) {
        return 0;
    }

    for (int v = 1; v <= n; v++) {
        if (v != parent && vis[u][v]) {
            int r = find_edge(v, u, target);
            if (r != -1) return max(r, mat[u][v]);
        }
    }
    return -1;
}

bool unique_mst()
{
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (mat[i][j] != INF && !vis[i][j]) {
                if (find_edge(i, j, j) == mat[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(mat, 0x3f, sizeof mat);
        memset(vis, 0, sizeof vis);
        memset(dist, 0x3f, sizeof dist);

        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            mat[u][v] = mat[v][u] = d;
        }

        mst = 0;
        dist[1] = 0;
        parent[1] = 0;
        for (int i = 0; i < n; i++) {
            int mindist = INF;
            int k;
            for (int j = 1; j <= n; j++) {
                if (dist[j] != -1 && dist[j] < mindist) {
                    mindist = dist[j];
                    k = j;
                }
            }
            mst += dist[k];
            dist[k] = -1;
            vis[parent[k]][k] = vis[k][parent[k]] = 1;
            for (int j = 1; j <= n; j++) {
                if (mat[k][j] < dist[j]) {
                    dist[j] = mat[k][j];
                    parent[j] = k;
                }
            }
        }

        if (unique_mst()) printf("%d\n", mst);
        else puts("Not Unique!");
    }

    return 0;
}

