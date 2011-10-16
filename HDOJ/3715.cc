/*
 *  SRC: HDOJ 3715
 * PROB: Go Deeper
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
const int MAX_N = 1010 << 1;

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

bool sat_2(int n)
{
    tarjan(n);

    for (int i = 0; i < n; i += 2)
        if (scc_id[i] == scc_id[i ^ 1]) return false;
    return true;
}

const int MAX_M = 10010;
int n, m;
int a[MAX_M], b[MAX_M], c[MAX_M];

bool check(int dep)
{
    for (int i = 0; i < n * 2; i++) edge[i].clear();
    for (int i = 0; i < dep; i++) {
        switch (c[i]) {
            case 0: edge[a[i] << 1].push_back((b[i] << 1) ^ 1);
                    edge[b[i] << 1].push_back((a[i] << 1) ^ 1);
                    break;
            case 1: edge[a[i] << 1].push_back(b[i] << 1);
                    edge[(a[i] << 1) ^ 1].push_back((b[i] << 1) ^ 1);
                    edge[b[i] << 1].push_back(a[i] << 1);
                    edge[(b[i] << 1) ^ 1].push_back((a[i] << 1) ^ 1);
                    break;
            case 2: edge[(a[i] << 1) ^ 1].push_back(b[i] << 1);
                    edge[(b[i] << 1) ^ 1].push_back(a[i] << 1);
        }
    }

    return sat_2(n * 2);
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) scanf("%d%d%d", a + i, b + i, c + i);

        int l = 1, r = m;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%d\n", l);
    }

    return 0;
}
