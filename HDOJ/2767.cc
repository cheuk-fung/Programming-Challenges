/*
 *  SRC: HDOJ 2767
 * PROB: Proving Equivalences
 * ALGO: Tarjan
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

typedef vector<int>::const_iterator vci;
const int MAX_N = 20010;

vector<int> edge[MAX_N];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAX_N], low[MAX_N], scc_no[MAX_N], scc_size[MAX_N];
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
            scc_no[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (v != u) ;
    }
}

void tarjan(int n)
{
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

int n, m;
int out_deg[MAX_N], in_deg[MAX_N];

int solve()
{
    if (scc_cnt == 1) return 0;

    for (int u = 1; u <= n; u++)
        for (vci v = edge[u].begin(); v != edge[u].end(); v++)
            if (scc_no[u] != scc_no[*v]) {
                out_deg[scc_no[u]]++;
                in_deg[scc_no[*v]]++;
            }

    int in_cnt = 0, out_cnt = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!in_deg[i]) in_cnt++;
        if (!out_deg[i]) out_cnt++;
    }

    return in_cnt > out_cnt ? in_cnt : out_cnt;
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%d%d", &n, &m);
        if (m == 0) {
            printf("%d\n", n);
            continue;
        }

        for (int i = 1; i <= n; i++) edge[i].clear();
        stack.clear();
        idx = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(scc_no, 0, sizeof(scc_no));
        memset(scc_size, 0, sizeof(scc_size));
        memset(in_stack, 0, sizeof(in_stack));
        memset(in_deg, 0, sizeof(in_deg));
        memset(out_deg, 0, sizeof(out_deg));

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[a].push_back(b);
        }

        tarjan(n);

        printf("%d\n", solve());
    }

    return 0;
}


