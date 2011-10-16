/*
 *  SRC: HDOJ 3062
 * PROB: Party
 * ALGO: 2-SAT
 * DATE: Oct 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

typedef vector<int>::const_iterator vci;
const int MAX_N = 2020;

vector<int> edge[MAX_N];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAX_N], low[MAX_N], scc_id[MAX_N], scc_size[MAX_N];
bool in_stack[MAX_N];

void tarjan_dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    in_stack[u] = true;
    stack.push_back(u);

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (!dfn[*v]) {
            tarjan_dfs(*v);
            if (low[*v] < low[u]) low[u] = low[*v];
        }
        else if (in_stack[*v])
            if (dfn[*v] < low[u]) low[u] = dfn[*v];
    }
    
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            in_stack[v] = false;
            scc_id[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (v != u) ;
    }
}

void tarjan(int n)
{
    idx = scc_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc_id, 0, sizeof(scc_id));
    memset(scc_size, 0, sizeof(scc_size));

    for (int i = 0; i < n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

int n, m;
int out_deg[MAX_N];

int solve()
{
    for (int i = 0; i < n * 2; i++) edge[i].clear();
    for (int i = 0; i < m; i++) {
        int a1, a2, c1, c2;
        scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
        edge[(a1 << 1) ^ c1].push_back((a2 << 1) ^ (c2 ^ 1));
        edge[(a2 << 1) ^ c2].push_back((a1 << 1) ^ (c1 ^ 1));
    }
    tarjan(n * 2);

    for (int i = 0; i < n * 2; i += 2)
        if (scc_id[i] == scc_id[i ^ 1]) return false;
    return true;
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
        puts(solve() ? "YES" : "NO");

    return 0;
}
