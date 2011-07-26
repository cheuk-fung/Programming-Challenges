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

const int MAX_N = 37 * 37;

vector<int> edge[MAX_N];
typedef vector<int>::const_iterator vci;

int n, m, k;
bool hole[37][37];

int match[MAX_N];
bool vis[MAX_N];

bool findPath(int u)
{
    for (vci v = edge[u].begin(); v != edge[u].end(); v++)
        if (!vis[*v]) {
            vis[*v] = true;
            int t = match[*v];
            match[*v] = u;
            if (t == -1 || findPath(t)) return true;
            match[*v] = t;
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
                if (findPath(i * m + j)) res++;
            }
    return res;
}

void buildGraph()
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

    buildGraph();

    if (hungarian() * 2 + k == n * m) puts("YES");
    else puts("NO");

    return 0;
}
