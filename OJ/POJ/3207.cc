/*
 *  SRC: POJ 3207
 * PROB: Ikki's Story IV - Panda's Trick
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

const int MAXN = 1010;

vector<int> edge[MAXN];
vector<int> S;
int tms, scccnt;
int dfn[MAXN], low[MAXN], sccid[MAXN];
bool inS[MAXN];

void tarjan_dfs(int u)
{
    S.push_back(u);
    inS[u] = true;
    dfn[u] = low[u] = tms++;

    for (int i = 0; i < (int)edge[u].size(); i++) {
        int v = edge[u][i];
        if (dfn[v] == -1) {
            tarjan_dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (inS[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        int v;
        do {
            v = S.back();
            S.pop_back();
            inS[v] = false;
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

struct Wire {
    int a, b;
} link[555];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &link[i].a, &link[i].b);
        if (link[i].a > link[i].b) swap(link[i].a, link[i].b);
    }
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if ((link[i].a < link[j].a && link[j].a < link[i].b) ^ (link[i].a < link[j].b && link[j].b < link[i].b)) {
                edge[i << 1].push_back(j << 1 | 1);
                edge[i << 1 | 1].push_back(j << 1);
                edge[j << 1].push_back(i << 1 | 1);
                edge[j << 1 | 1].push_back(i << 1);
            }
        }
    }

    puts(sat(m << 1) ? "panda is telling the truth..." : "the evil panda is lying again");

    return 0;
}

