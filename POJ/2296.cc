/*
 *  SRC: POJ 2296
 * PROB: Map Labeler
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

int n;
pii pnt[MAXN];

struct Rectangle {
    int x1, y1, x2, y2;

    Rectangle(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) { }
};

bool overlap(const Rectangle &R1, const Rectangle &R2)
{
    return (R1.x1 <= R2.x1 && R2.x1 <  R1.x2 && R1.y1 <= R2.y1 && R2.y1 <  R1.y2)
        || (R1.x1 <= R2.x1 && R2.x1 <  R1.x2 && R1.y1 <  R2.y2 && R2.y2 <= R1.y2)
        || (R1.x1 <  R2.x2 && R2.x2 <= R1.x2 && R1.y1 <= R2.y1 && R2.y1 <  R1.y2)
        || (R1.x1 <  R2.x2 && R2.x2 <= R1.x2 && R1.y1 <  R2.y2 && R2.y2 <= R1.y2);
}

bool check(int d)
{
    for (int i = 0; i < n << 1; i++) edge[i].clear();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Rectangle A(pnt[i].first, pnt[i].second - d, pnt[i].first + 2 * d, pnt[i].second + d);
            Rectangle B(pnt[i].first - 2 * d, pnt[i].second - d, pnt[i].first, pnt[i].second + d);
            Rectangle C(pnt[j].first, pnt[j].second - d, pnt[j].first + 2 * d, pnt[j].second + d);
            Rectangle D(pnt[j].first - 2 * d, pnt[j].second - d, pnt[j].first, pnt[j].second + d);

            if (overlap(A, C)) {
                edge[i << 1].push_back(j << 1 | 1);
                edge[j << 1].push_back(i << 1 | 1);
            }
            if (overlap(A, D)) {
                edge[i << 1].push_back(j << 1);
                edge[j << 1 | 1].push_back(i << 1 | 1);
            }
            if (overlap(B, C)) {
                edge[i << 1 | 1].push_back(j << 1 | 1);
                edge[j << 1].push_back(i << 1);
            }
            if (overlap(B, D)) {
                edge[i << 1 | 1].push_back(j << 1);
                edge[j << 1 | 1].push_back(i << 1);
            }
        }
    }
    return sat(n << 1);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].second, &pnt[i].first);
            pnt[i].first <<= 1;
            pnt[i].second <<= 1;
        }

        int low = 0, high = 100000;
        while (low < high) {
            int mid = (low + high + 1) >> 1;
            if (check(mid)) low = mid;
            else high = mid - 1;
        }

        printf("%d\n", low);
    }

    return 0;
}
