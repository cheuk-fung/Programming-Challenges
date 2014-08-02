/*
 *  SRC: POJ 2288
 * PROB: Islands and Bridges
 * ALGO: DP
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int val[13], mat[13][13];
int f[1 << 13][13][13];
long long g[1 << 13][13][13];
vector<int> e[13];

inline int countbitone(int x)
{
    x = (x & 0x55555555) + (x >>  1 & 0x55555555);
    x = (x & 0x33333333) + (x >>  2 & 0x33333333);
    x = (x & 0x0f0f0f0f) + (x >>  4 & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + (x >>  8 & 0x00ff00ff);
    x = (x & 0x0000ffff) + (x >> 16 & 0x0000ffff);
    return x;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);

        memset(mat, 0, sizeof mat);
        for (int i = 0; i < n; i++) e[i].clear();

        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", val + i);
            sum += val[i];
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            mat[u][v] = mat[v][u] = 1;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        if (n == 1) {
            printf("%d %d\n", val[0], 1);
            continue;
        }

        memset(f, 0xff, sizeof f);
        for (int u = 0; u < n; u++) {
            for (int i = 0; i < (int)e[u].size(); i++) {
                int v = e[u][i];
                f[1 << u | 1 << v][u][v] = sum + val[u] * val[v];
                g[1 << u | 1 << v][u][v] = 1;
            }
        }

        for (int l = 2; l <= n; l++) {
            for (int s = 0; s < 1 << n; s++) {
                if (countbitone(s) != l)  continue;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (f[s][i][j] == -1) continue;
                        int u = j;
                        for (int k = 0; k < (int)e[j].size(); k++) {
                            int v = e[j][k];
                            if (s & 1 << v) continue;
                            int ns = s | 1 << v;
                            int addition = val[u] * val[v];
                            if (mat[v][i]) addition += val[i] * val[u] * val[v];
                            if (f[s][i][j] + addition > f[ns][u][v]) {
                                f[ns][u][v] = f[s][i][j] + addition;
                                g[ns][u][v] = g[s][i][j];
                            } else if (f[s][i][j] + addition == f[ns][u][v]) {
                                g[ns][u][v] += g[s][i][j];
                            }
                        }
                    }
                }
            }
        }

        int best = 0;
        long long bestcnt = 0;
        for (int i = 0, s = (1 << n) - 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (f[s][i][j] > best) {
                    best = f[s][i][j];
                    bestcnt = g[s][i][j];
                } else if (f[s][i][j] == best) {
                    bestcnt += g[s][i][j];
                }
            }
        }

        printf("%d %lld\n", best, bestcnt / 2);
    }

    return 0;
}

