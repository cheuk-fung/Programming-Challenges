/*
 *  SRC: HDOJ 4337
 * PROB: King Arthur's Knights
 * ALGO: Ore's Theorem
 * DATE: Aug 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
bool isfriend[MAXN][MAXN];
int cycle[MAXN];

int main(int argc, char *argv[])
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(isfriend, 0, sizeof isfriend);

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            isfriend[u][v] = isfriend[v][u] = true;
        }

        for (int i = 0; i < n; i++) cycle[i] = i + 1;
        for (int times = 0; times < n; times++) {
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                if (!isfriend[cycle[i]][cycle[j]]) {
                    for (int k = 0; k < n; k++) {
                        int l = (k + 1) % n;
                        if (i == k || i == l || j == k || j == l) continue;
                        if (isfriend[cycle[i]][cycle[k]] && isfriend[cycle[j]][cycle[l]]) {
                            if (j < k) {
                                reverse(cycle + j, cycle + k + 1);
                            } else {
                                reverse(cycle + l, cycle + i + 1);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%d%c", cycle[i], i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}
