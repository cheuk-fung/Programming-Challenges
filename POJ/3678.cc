/*
 *  SRC: POJ 3678
 * PROB: Katu Puzzle
 * ALGO: 2-SAT
 * DATE: Sep 20, 2012
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
vector<int> S;
int tms, scccnt;
int dfn[MAXN], low[MAXN], sccid[MAXN];
bool instack[MAXN];

void tarjan_dfs(int u)
{
    S.push_back(u);
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
            v = S.back();
            S.pop_back();
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
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        char op[10];
        scanf("%d%d%d%s", &a, &b, &c, op);
        switch (op[0]) {
            case 'A':
                edge[a << 1 | 1].push_back(b << 1 | c);
                edge[b << 1 | 1].push_back(a << 1 | c);
                if (c == 1) {
                    edge[a << 1].push_back(a << 1 | 1);
                    edge[b << 1].push_back(b << 1 | 1);
                }
                break;
            case 'O':
                edge[a << 1].push_back(b << 1 | c);
                edge[b << 1].push_back(a << 1 | c);
                if (c == 0) {
                    edge[a << 1 | 1].push_back(a << 1);
                    edge[b << 1 | 1].push_back(b << 1);
                }
                break;
            case 'X':
                edge[a << 1].push_back(b << 1 | c);
                edge[b << 1].push_back(a << 1 | c);
                edge[a << 1 | 1].push_back(b << 1 | !c);
                edge[b << 1 | 1].push_back(a << 1 | !c);
        }
    }

    bool r = sat(n << 1);
    puts(r ? "YES" : "NO");

    return 0;
}

