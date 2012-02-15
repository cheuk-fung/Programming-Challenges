/*
 *  SRC: POJ 2186
 * PROB: Popular Cows
 * ALGO: Tarjan(Strongly Connected Component)
 * DATE: Jul 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

typedef vector<int>::const_iterator vci;
const int MAXN = 10010;

vector<int> edge[MAXN];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAXN], low[MAXN], scc_id[MAXN], scc_size[MAXN];
bool in_stack[MAXN];

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

 // for (int i = 0; i < n; i++)
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

int n, m;
int out_deg[MAXN];

int solve()
{
    if (scc_cnt == 1) return n;

    for (int u = 1; u <= n; u++)
        for (vci v = edge[u].begin(); v != edge[u].end(); v++)
            if (scc_id[u] != scc_id[*v]) out_deg[scc_id[u]]++;

    int ans = 0, ans_cnt = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (out_deg[i] == 0) {
            ans = scc_size[i];
            ans_cnt++;
        }

    return ans_cnt == 1 ? ans : 0;
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        edge[a].push_back(b);
    }

    tarjan(n);

    printf("%d\n", solve());

    return 0;
}
