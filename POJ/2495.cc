/*
 *  SRC: POJ 2495
 * PROB: Incomplete chess boards
 * ALGO: Hungarian
 * DATE: Jul 27, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

const int MAX_N = 10 * 10;

vector<int> edge[MAX_N];
typedef vector<int>::const_iterator vci;

int n = 8, m = 8;
bool hole[10][10];

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
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        memset(hole, false, sizeof(hole));
        for (int j = 0; j < MAX_N; j++)
            edge[j].clear();

        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        hole[a - 1][b - 1] = true;
        hole[c - 1][d - 1] = true;

        buildGraph();

        printf("Scenario #%d:\n", i);
        if (hungarian() == 31) puts("1");
        else puts("0");
        puts("");
    }

    return 0;
}

