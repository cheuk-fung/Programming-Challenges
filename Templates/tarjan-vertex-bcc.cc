/*
 *  SRC: poj 2942
 * PROB: Knights of the Round Table
 * ALGO: Tarjan Vertex BCC (Vertex Biconnected Component
 * DATE: Jul 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int>::const_iterator vci;
const int MAXN = 1010;

vector<int> edge[MAXN];

vector<int> stack;
int idx, bcc_cnt;
int dfn[MAXN], low[MAXN];
vector<int> bcc_block[MAXN];
bool in_stack[MAXN];

void tarjan_dfs(int u, int parent)
{
    stack.push_back(u);
    in_stack[u] = true;
    dfn[u] = low[u] = idx++;

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (*v == parent) continue;
        if (dfn[*v] == -1) {
            tarjan_dfs(*v, u);
            low[u] = min(low[u], low[*v]);
            if (dfn[u] <= low[*v]) {
                int p;
                do {
                    p = stack.back();
                    stack.pop_back();
                    in_stack[p] = false;
                    bcc_block[bcc_cnt].push_back(p);
                } while (p != *v) ;
                bcc_block[bcc_cnt++].push_back(u);
            }
        } else if (in_stack[*v]) {
            low[u] = min(low[u], dfn[*v]);
        }
    }
}

void tarjan(int n)
{
    for (int i = 0; i < bcc_cnt; i++) bcc_block[i].clear();
    stack.clear();
    idx = bcc_cnt = 0;
    memset(dfn, 0xff, sizeof dfn);
    memset(low, 0xff, sizeof low);
    for (int i = 0; i < n; i++)
        if (dfn[i] == -1) tarjan_dfs(i , -1);
}

int mat[MAXN][MAXN];
bool color[MAXN], to_dye[MAXN], vis[MAXN];
bool expel[MAXN];

bool dye_dfs(int u, bool col)
{
    vis[u] = true;
    color[u] = col;
    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (to_dye[*v]) {
            if (!vis[*v]) {
                if (dye_dfs(*v, col ^ 1)) return true;
            } else if (col == color[*v]) {
                return true;
            }
        }
    }
    return false;
}

void dye()
{
    memset(expel, true, sizeof expel);
    for (int i = 0; i < bcc_cnt; i++) {
        memset(to_dye, false, sizeof to_dye);
        memset(vis, false, sizeof vis);
        for (int j = 0; j < bcc_block[i].size(); j++) to_dye[bcc_block[i][j]] = true;
        if (dye_dfs(bcc_block[i].back(), 0)) {
            for (int j = 0; j < bcc_block[i].size(); j++) expel[bcc_block[i][j]] = false;
        }
    }
}

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        memset(mat, 0, sizeof mat);
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--; y--;
            mat[x][y] = mat[y][x] = 1;
        }

        for (int i = 0; i < n; i++) {
            edge[i].clear();
            for (int j = 0; j < n; j++) {
                if (i != j && !mat[i][j]) edge[i].push_back(j);
            }
        }

        tarjan(n);
        dye();

        int ans = 0;
        for (int i = 0; i < n; i++)
            if (expel[i]) ans++;
        printf("%d\n", ans);
    }

    return 0;
}

