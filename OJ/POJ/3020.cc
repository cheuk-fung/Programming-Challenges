/*
 *  SRC: POJ 3020
 * PROB: Antenna Placement
 * ALGO: Hungarian
 * DATE: Mar 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

typedef vector<int>::const_iterator vci;

const int MAXN = 500;

int n, m;
bool map[40][10];
int match[MAXN];
bool vis[MAXN];
vector<int> edge[MAXN];

bool find_path(int u)
{
    for (vci v = edge[u].begin(); v != edge[u].end(); v++)
        if (!vis[*v]) {
            vis[*v] = true;
            if (match[*v] == -1 || find_path(match[*v])) {
                match[*v] = u;
                return true;
            }
        }
    return false;
}

int hungarian()
{
    int res = 0;
    memset(match, 0xff, sizeof(match));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            if (map[i][j]) {
                memset(vis, 0, sizeof(vis));
                if (find_path(i * m + j)) res++;
            }
    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d%d", &n, &m);
        memset(map, 0, sizeof(map));
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                edge[i * m + j].clear();
                char c;
                scanf(" %c", &c);
                if (c == '*') {
                    map[i][j] = true;
                    cnt++;
                }
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (map[i][j]) {
                    int id = i * m + j;
                    if (i - 1 >= 0 && map[i - 1][j])
                        edge[id].push_back((i - 1) * m + j);
                    if (i + 1 < n && map[i + 1][j])
                        edge[id].push_back((i + 1) * m + j);
                    if (j - 1 >= 0 && map[i][j - 1])
                        edge[id].push_back(i * m + j - 1);
                    if (j + 1 < m && map[i][j + 1])
                        edge[id].push_back(i * m + j + 1);
                }

        int pairs = hungarian();
        printf("%d\n", pairs / 2 + (cnt - pairs));
    }

    return 0;
}

