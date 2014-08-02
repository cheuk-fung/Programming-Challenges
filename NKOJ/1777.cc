/*
 *  SRC: NKOJ p1777
 * PROB: Popular Cows
 * ALGO: Tarjan(Strongly Connected Component)
 * DATE: Jul 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>

using std::vector;

typedef vector<int>::const_iterator vci;
const int MAX_N = 10010;

vector<int> edge[MAX_N];

vector<int> stack;
int idx, sccCnt;
int dfn[MAX_N], low[MAX_N], sccNo[MAX_N], sccSize[MAX_N];
bool inStack[MAX_N];

void tarjanDFS(int u)
{
    dfn[u] = low[u] = ++idx;
    inStack[u] = true;
    stack.push_back(u);

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (!dfn[*v]) {
            tarjanDFS(*v);
            if (low[*v] < low[u]) low[u] = low[*v];
        }
        else if (inStack[*v])
            if (dfn[*v] < low[u]) low[u] = dfn[*v];
    }
    
    if (dfn[u] == low[u]) {
        sccCnt++;
        int v;
        do {
            v = stack.back();
            stack.pop_back();
            inStack[v] = false;
            sccNo[v] = sccCnt;
            sccSize[sccCnt]++;
        } while (v != u) ;
    }
}

void tarjan(int n)
{
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjanDFS(i);
}

int n, m;
int outDegree[MAX_N];

int solve()
{
    if (sccCnt == 1) return n;

    for (int u = 1; u <= n; u++)
        for (vci v = edge[u].begin(); v != edge[u].end(); v++)
            if (sccNo[u] != sccNo[*v]) outDegree[sccNo[u]]++;

    int ans = 0, ansCnt = 0;
    for (int i = 1; i <= sccCnt; i++)
        if (outDegree[i] == 0) {
            ans = sccSize[i];
            ansCnt++;
        }

    return ansCnt == 1 ? ans : 0;
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

