/*
 *  SRC: HDOJ 3622
 * PROB: Bomb Game
 * ALGO: 2-SAT
 * DATE: Sep 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
typedef pair<int, int> pii;

const double eps = 1e-6;
const int MAXN = 209;
vector<int> edge[MAXN];
vector<int> S(MAXN);
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

    if (low[u] == dfn[u]) {
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

int n;
pii pnt[MAXN];

template<typename T> inline T SQR(T x) { return x * x; }
inline int dist(const pii &a, const pii &b) { return SQR(a.first - b.first) + SQR(a.second - b.second); }

bool check(double r)
{
    for (int i = 0; i < n << 1; i++) edge[i].clear();

    r = SQR(r * 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist(pnt[i << 1], pnt[j << 1]) + eps < r) {
                edge[i << 1].push_back(j << 1 | 1);
                edge[j << 1].push_back(i << 1 | 1);
            }
            if (dist(pnt[i << 1], pnt[j << 1 | 1]) + eps < r) {
                edge[i << 1].push_back(j << 1);
                edge[j << 1 | 1].push_back(i << 1 | 1);
            }
            if (dist(pnt[i << 1 | 1], pnt[j << 1]) + eps < r) {
                edge[i << 1 | 1].push_back(j << 1 | 1);
                edge[j << 1].push_back(i << 1);
            }
            if (dist(pnt[i << 1 | 1], pnt[j << 1 | 1]) + eps < r) {
                edge[i << 1 | 1].push_back(j << 1);
                edge[j << 1 | 1].push_back(i << 1);
            }
        }
    }
    return sat(n << 1);
}

int main()
{
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            pnt[i << 1] = pii(x1, y1);
            pnt[i << 1 | 1] = pii(x2, y2);
        }

        double low = 0, high = 1e8;
        while (low + 1e-6 < high) {
            double mid = (low + high) / 2;
            if (check(mid)) low = mid;
            else high = mid;
        }

        printf("%.2f\n", low);
    }

    return 0;
}

