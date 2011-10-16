/*
 *  SRC: POJ 3648
 * PROB: Wedding
 * ALGO: 2-SAT
 * DATE: Oct 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

typedef vector<int>::const_iterator vci;
const int MAX_N = 1010 << 1;

vector<int> edge[MAX_N];
vector<int> new_edge[MAX_N];

vector<int> stack;
int idx, scc_cnt;
int dfn[MAX_N], low[MAX_N], scc_id[MAX_N], scc_size[MAX_N];
bool in_stack[MAX_N];

int in_deg[MAX_N], color[MAX_N];

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

void color_dfs(int u)
{
    color[u] = 2;
    for (vci v = new_edge[u].begin(); v != new_edge[u].end(); v++)
        if (!color[*v]) color_dfs(*v);
}

bool sat_2(int n)
{
    tarjan(n);

    for (int i = 0; i < n; i += 2)
        if (scc_id[i] == scc_id[i ^ 1]) return false;

    memset(in_deg, 0, sizeof(in_deg));
    for (int u = 0; u < n; u++)
        for (vci v = edge[u].begin(); v != edge[u].end(); v++)
            if (scc_id[u] != scc_id[*v]) {
                new_edge[scc_id[*v]].push_back(scc_id[u]);
                in_deg[scc_id[u]]++;
            }

    queue<int> Q;
    vector<int> topo;
    for (int i = 1; i <= scc_cnt; i++)
        if (!in_deg[i]) Q.push(i);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        topo.push_back(u);
        for (vci v = new_edge[u].begin(); v != new_edge[u].end(); v++)
            if (--in_deg[*v] == 0) Q.push(*v);
    }

    memset(color, 0, sizeof(color));
    for (vci u = topo.begin(); u != topo.end(); u++)
        if (!color[*u]) {
            color[*u] = 1;
            for (int i = 0; i < n; i++)
                if (scc_id[i] == *u)
                    if (!color[scc_id[i ^ 1]])
                        color_dfs(scc_id[i ^ 1]);
        }

    return true;
}

inline int which(char c) { return c == 'w' ? 0 : 1; }

int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 0; i < n * 2; i++) {
            edge[i].clear();
            new_edge[i].clear();
        }

        for (int i = 0; i < m; i++) {
            int  id1, id2;
            char hw1, hw2;
            scanf("%d%c%d%c", &id1, &hw1, &id2, &hw2);
            edge[(id1 << 1) ^ which(hw1)].push_back((id2 << 1) ^ (!which(hw2)));
            edge[(id2 << 1) ^ which(hw2)].push_back((id1 << 1) ^ (!which(hw1)));
        }
        edge[0].push_back(1);

        if (!sat_2(n * 2)) {
            puts("bad luck");
            continue;
        }

        int c = color[scc_id[0]];
        bool first = true;
        for (int i = 2; i < n * 2; i++)
            if (color[scc_id[i]] == c) {
                if (!first) putchar(' ');
                printf("%d%c", i >> 1, (i & 1) ? 'h' : 'w');
                first = false;
            }
        putchar(10);
    }

    return 0;
}
