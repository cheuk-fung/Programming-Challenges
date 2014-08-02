/*
 *  SRC: HDOJ 3836
 * PROB: Equivalent Sets
 * ALGO: Tarjan
 * DATE: Apr 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef vector<int>::const_iterator vci;
typedef set<int>::const_iterator sci;
const int MAXN = 20020;

vector<int> edge[MAXN];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAXN], low[MAXN], scc_id[MAXN], scc_size[MAXN];
bool in_stack[MAXN];

int in_deg[MAXN], out_deg[MAXN];

void tarjan_dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    in_stack[u] = true;
    stack.push_back(u);

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
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

    for (int i = 0; i < n; i++) {
        if (!dfn[i]) tarjan_dfs(i);
    }
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) {
            edge[i].clear();
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[a - 1].push_back(b - 1);
        }

        tarjan(n);

        if (scc_cnt == 1) {
            puts("0");
            continue;
        }

        memset(in_deg, 0, sizeof(in_deg));
        memset(out_deg, 0, sizeof(out_deg));
        for (int u = 0; u < n; u++) {
            for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
                if (scc_id[u] != scc_id[*v]) {
                    in_deg[scc_id[*v]]++;
                    out_deg[scc_id[u]]++;
                }
            }
        }

        int in_zero_cnt = 0, out_zero_cnt = 0;
        for (int i = 0; i < scc_cnt; i++) {
            if (!in_deg[i]) in_zero_cnt++;
            if (!out_deg[i]) out_zero_cnt++;
        }

        printf("%d\n", max(in_zero_cnt, out_zero_cnt));
    }

    return 0;
}
