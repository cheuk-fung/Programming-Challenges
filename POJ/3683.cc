/*
 *  SRC: POJ 3683
 * PROB: Priest John's Busiest Day
 * ALGO: 2-SAT
 * DATE: Sep 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int RED = 1;
const int BLUE = 2;
const int MAXN = 2012;

vector<int> edge[MAXN];
vector<int> newedge[MAXN];
stack<int> S;

int tms, scccnt;
int dfn[MAXN], low[MAXN], sccid[MAXN];
bool instack[MAXN];
int indeg[MAXN], color[MAXN];

void tarjan_dfs(int u)
{
    S.push(u);
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
            v = S.top();
            S.pop();
            instack[v] = false;
            sccid[v] = scccnt;
        } while (v != u);
        scccnt++;
    }
}

void tarjan(int n)
{
    tms = scccnt = 0;
    memset(dfn, 0xff, sizeof dfn);

    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            tarjan_dfs(i);
        }
    }
}

void dye(int u)
{
    color[u] = BLUE;
    for (int i = 0; i < (int)newedge[u].size(); i++) {
        int v = newedge[u][i];
        if (!color[v]) {
            dye(v);
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

    for (int u = 0; u < n; u++) {
        for (int i = 0; i < (int)edge[u].size(); i++) {
            int v = edge[u][i];
            if (sccid[u] != sccid[v]) {
                newedge[sccid[v]].push_back(sccid[u]);
                indeg[sccid[u]]++;
            }
        }
    }

    queue<int> Q;
    vector<int> topo;
    for (int i = 0; i < scccnt; i++) {
        if (indeg[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        topo.push_back(u);

        for (int i = 0; i < (int)newedge[u].size(); i++) {
            int v = newedge[u][i];
            if (--indeg[v] == 0) {
                Q.push(v);
            }
        }
    }

    for (int i = 0; i < (int)topo.size(); i++) {
        int u = topo[i];
        if (!color[u]) {
            color[u] = RED;
            for (int i = 0; i < n; i++) {
                if (sccid[i] == u && !color[sccid[i ^ 1]]) {
                    dye(sccid[i ^ 1]);
                }
            }
        }
    }

    return true;
}

struct Wedding {
    int begin, end;
} wedding[MAXN >> 1];

inline bool overlap(int x1, int y1, int x2, int y2)
{
    return (x1 <= x2 && x2 < y1) || (x2 <= x1 && x1 < y2);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int shour, smin, thour, tmin, d;
        scanf("%d:%d%d:%d%d", &shour, &smin, &thour, &tmin, &d);
        wedding[i << 1].begin = shour * 60 + smin;
        wedding[i << 1].end = shour * 60 + smin + d;
        wedding[i << 1 | 1].begin = thour * 60 + tmin - d;
        wedding[i << 1 | 1].end = thour * 60 + tmin;
    }
    for (int i = 0; i < n << 1; i++) {
        for (int j = i + 1; j < n << 1; j++) {
            if ((i ^ 1) == j) continue;
            if (overlap(wedding[i].begin, wedding[i].end, wedding[j].begin, wedding[j].end)) {
                edge[i].push_back(j ^ 1);
                edge[j].push_back(i ^ 1);
            }
        }
    }

    bool ok = sat(n << 1);
    puts(ok ? "YES" : "NO");
    if (ok) {
        for (int i = 0; i < n; i++) {
            int x = i << 1 | (color[sccid[i << 1]] != RED);
            printf("%02d:%02d ", wedding[x].begin / 60, wedding[x].begin % 60);
            printf("%02d:%02d\n", wedding[x].end / 60, wedding[x].end % 60);
        }
    }

    return 0;
}

