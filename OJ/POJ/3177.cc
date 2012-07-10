/*
 *  SRC: POJ 3177
 * PROB: Redundant Paths
 * ALGO: Tarjan Edge BCC
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
const int MAXN = 5010;

vector<int> edge[MAXN];
int mat[MAXN][MAXN];

vector<int> stack;
int idx, bcc_cnt;
int dfn[MAXN], low[MAXN], bcc_id[MAXN], bcc_size[MAXN];
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
        } else if (in_stack[*v]) {
            low[u] = min(low[u], dfn[*v]);
        }
    }

    if (dfn[u] == low[u] && (parent == -1 || mat[parent][u] == 1)) {
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            in_stack[v] = false;
            bcc_id[v] = bcc_cnt;
            bcc_size[bcc_cnt]++;
        } while (v != u) ;
        bcc_cnt++;
    }
}

void tarjan(int n)
{
    idx = bcc_cnt = 0;
    memset(dfn, 0xff, sizeof(dfn));
    memset(low, 0xff, sizeof(low));
    memset(bcc_id, 0xff, sizeof(bcc_id));
    memset(bcc_size, 0, sizeof(bcc_size));

    for (int i = 0; i < n; i++)
        if (dfn[i] == -1) tarjan_dfs(i, -1);
}

int degree[MAXN];

int count_leaves(int n)
{
    memset(degree, 0, sizeof(degree));
    for (int u = 0; u < n; u++) {
        for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
            if (bcc_id[u] != bcc_id[*v]) {
                degree[bcc_id[u]]++;
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < bcc_cnt; i++) {
        if (degree[i] == 1) cnt++;
    }

    return cnt;
}

int main()
{
    int f, r;
    scanf("%d%d", &f, &r);

    for (int i = 0; i < r; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
        mat[u][v]++;
        mat[v][u]++;
    }

    tarjan(f);
    printf("%d\n", (count_leaves(f) + 1) >> 1);

    return 0;
}
