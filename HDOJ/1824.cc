/*
 *  SRC: HDOJ 1824
 * PROB: Let's go home
 * ALGO: 2-SAT
 * DATE: Sep 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2012;

vector<int> edge[MAXN];
vector<int> stack;
int tms, scccnt;
int dfn[MAXN], low[MAXN], sccid[MAXN];
bool instack[MAXN];

int idx[MAXN << 1];

void tarjan_dfs(int u)
{
    stack.push_back(u);
    instack[u] = true;
    dfn[u] = low[u] = tms++;

    for (int i = 0; i < (int)edge[u].size(); i++) {
        int v = edge[u][i];
        if (dfn[v] == -1) {
            tarjan_dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            instack[v] = false;
            sccid[v] = scccnt;
        } while (v != u) ;
        scccnt++;
    }
}

void tarjan(int n)
{
    tms = scccnt = 0;
    memset(dfn, 0xff, sizeof dfn);
    memset(low, 0xff, sizeof low);
    memset(sccid, 0xff, sizeof sccid);

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan_dfs(i);
        }
    }
}

bool sat(int n)
{
    tarjan(n);
    for (int i = 0; i < n; i += 2) {
        if (sccid[i] == sccid[i ^ 1]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n << 1; i++) edge[i].clear();
        for (int i = 0; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            idx[a] = i << 1;
            idx[b] = idx[c] = i << 1 | 1;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[idx[a]].push_back(idx[b] ^ 1);
            edge[idx[b]].push_back(idx[a] ^ 1);
        }

        puts(sat(n << 1) ? "yes" : "no");
    }

    return 0;
}

