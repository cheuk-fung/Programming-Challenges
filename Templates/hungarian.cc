/*
 *  SRC: POJ 2446
 * PROB: Chessboard
 * ALGO: Hungarian
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

const int MAXN = 37 * 37;

vector<int> edge[MAXN];
typedef vector<int>::const_iterator vci;

int n, m, k;
bool hole[37][37];

int match[MAXN];
bool vis[MAXN];

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
            if (((i + j) & 1) == 0 && !hole[i][j]) {
                memset(vis, 0, sizeof(vis));
                if (find_path(i * m + j)) res++;
            }
    return res;
}

void build_graph()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (((i + j) & 1) == 0 && !hole[i][j]) {
                if (i - 1 >= 0 && !hole[i - 1][j]) {
                    edge[i * m + j].push_back((i - 1) * m + j);
                    edge[(i - 1) * m + j].push_back(i * m + j);
                }
                if (i + 1 < n && !hole[i + 1][j]) {
                    edge[i * m + j].push_back((i + 1) * m + j);
                    edge[(i + 1) * m + j].push_back(i * m + j);
                }
                if (j - 1 >= 0 && !hole[i][j - 1]) {
                    edge[i * m + j].push_back(i * m + j - 1);
                    edge[i * m + j - 1].push_back(i * m + j);
                }
                if (j + 1 < m && !hole[i][j + 1]) {
                    edge[i * m + j].push_back(i * m + j + 1);
                    edge[i * m + j + 1].push_back(i * m + j);
                }
            }
}

int main()
{
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &y, &x);
        hole[x - 1][y - 1] = true;
    }

    build_graph();

    if (hungarian() * 2 + k == n * m) puts("YES");
    else puts("NO");

    return 0;
}
