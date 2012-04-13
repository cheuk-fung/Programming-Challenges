/*
 *  SRC: HDOJ 3861
 * PROB: The King’s Problem
 * ALGO: Tarjan + Hungaian
 * DATE: Apr 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;

typedef vector<int>::const_iterator vci;
const int MAXN = 10010;

vector<int> scc_edge[MAXN];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAXN], low[MAXN], scc_id[MAXN], scc_size[MAXN];
bool in_stack[MAXN];

void tarjan_dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    in_stack[u] = true;
    stack.push_back(u);

    for (vci v = scc_edge[u].begin(); v != scc_edge[u].end(); v++) {
        if (!dfn[*v]) {
            tarjan_dfs(*v);
            low[u] = min(low[u], low[*v]);
        } else if (in_stack[*v]) {
            low[u] = min(low[u], dfn[*v]);
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            in_stack[v] = false;
            scc_id[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (v != u) ;
        scc_cnt++;
    }
}

void tarjan(int n)
{
    idx = scc_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc_id, 0xff, sizeof(scc_id));
    memset(scc_size, 0, sizeof(scc_size));

    for (int i = 0; i < n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

vector<int> new_edge[MAXN];

int match[MAXN];
bool vis[MAXN];

bool find_path(int u)
{
    for (vci v = new_edge[u].begin(); v != new_edge[u].end(); v++)
        if (!vis[*v]) {
            vis[*v] = true;
            if (match[*v] == -1 || find_path(match[*v])) {
                match[*v] = u;
                return true;
            }
        }

    return false;
}

int hungarian(int n)
{
    int res = 0;
    memset(match, 0xff, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if (find_path(i)) res++;
    }

    return res;
}


int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scc_edge[i].clear();
        }

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            scc_edge[u - 1].push_back(v - 1);
        }

        tarjan(n);
        for (int i = 0; i < scc_cnt << 1; i++) {
            new_edge[i].clear();
        }

        for (int u = 0; u < n; u++) {
            for (vci v = scc_edge[u].begin(); v != scc_edge[u].end(); v++) {
                if (scc_id[u] != scc_id[*v]) {
                    new_edge[scc_id[u]].push_back(scc_id[*v] + scc_cnt);
                }
            }
        }

        printf("%d\n", scc_cnt - hungarian(scc_cnt << 1));
    }

    return 0;
}

