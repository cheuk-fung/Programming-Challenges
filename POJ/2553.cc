/*
 *  SRC: POJ 2553
 * PROB: The Bottom of a Graph
 * ALGO: Tarjan
 * DATE: Sep 09, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using std::sort;
using std::vector;

typedef vector<int>::const_iterator vci;
const int MAX_N = 5010;

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

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

int n, m;
int out_deg[MAX_N];
vector<int> ans;

void solve()
{
    memset(out_deg, 0, sizeof(out_deg));

    for (int u = 1; u <= n; u++)
        for (vci v = edge[u].begin(); v != edge[u].end(); v++)
            if (scc_id[u] != scc_id[*v]) out_deg[scc_id[u]]++;

    for (int i = 1; i <= scc_cnt; i++)
        if (out_deg[i] == 0) {
            for (int j = 1; j <= n; j++)
                if (scc_id[j] == i) ans.push_back(j);
        }

    if (ans.empty()) {
        putchar(10);
        return ;
    }

    sort(ans.begin(), ans.end());

    printf("%d", *ans.begin());
    for (vci p = ans.begin() + 1; p != ans.end(); p++)
        printf(" %d", *p);
    putchar(10);

    ans.clear();
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[a].push_back(b);
        }
        tarjan(n);
        solve();
        for (int i = 1; i <= n; i++)
            edge[i].clear();
    }

    return 0;
}
