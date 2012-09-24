/*
 *  SRC: HDOJ 4280
 * PROB: Island Transport
 * ALGO: Minimum Cut -> SSSP
 * DATE: Sep 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;
const int NEGINF = 0xc0c0c0c0;

struct Point {
    int x, y;

    bool operator<(const Point &o) const { return x< o.x; }
} pnt[MAXN];

struct Edge {
    int v, d;
};
vector<Edge> e[MAXN];

struct Arc {
    int v, d;
    int eid;
    double agl;

    bool operator<(const Arc &o) const { return agl < o.agl; }
};
vector<Arc> arc[MAXN];
int col[MAXN << 1], next[MAXN << 1];
int dist[MAXN], inque[MAXN];

inline double angle(int u, int v) { return atan2(pnt[v].y - pnt[u].y, pnt[v].x - pnt[u].x); }

int spfa(int s, int t)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(inque, false, sizeof(inque));
    dist[s] = 0;

    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;
        for (int i = 0; i < (int)e[u].size(); i++) {
            int v = e[u][i].v;
            int d = e[u][i].d;
            if (dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;
                if (!inque[v]) {
                    que.push(v);
                    inque[v] = true;
                }
            }
        }
    }

    return dist[t];
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].x, &pnt[i].y);
            arc[i].clear();
        }

        int eid = 0;
        int s = min_element(pnt, pnt + n) - pnt;
        int t = max_element(pnt, pnt + n) - pnt;
        arc[s].push_back((Arc){t, INF, eid++, acos(-1.0)});
        arc[t].push_back((Arc){s, INF, eid++, 0});
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            u--; v--;
            arc[u].push_back((Arc){v, d, eid++, angle(u, v)});
            arc[v].push_back((Arc){u, d, eid++, angle(v, u)});
        }
        for (int i = 0; i < n; i++) {
            sort(arc[i].begin(), arc[i].end());
            for (int j = 0; j < (int)arc[i].size() - 1; j++) {
                next[arc[i][j].eid ^ 1] = arc[i][j + 1].eid;
            }
            next[arc[i][arc[i].size() - 1].eid ^ 1] = arc[i][0].eid;
        }

        memset(col, 0xff, sizeof col);
        int cid = 0;
        for (int i = 0; i < eid; i++) {
            if (col[i] == -1) {
                for (int x = i; col[x] == -1; x = next[x]) {
                    col[x] = cid;
                }
                cid++;
            }
        }
        for (int i = 0; i < cid; i++) e[i].clear();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < (int)arc[i].size(); j++) {
                e[col[arc[i][j].eid]].push_back((Edge){col[arc[i][j].eid ^ 1], arc[i][j].d});
            }
        }

        int r = spfa(col[0], col[1]);
        printf("%d\n", r);
    }

    return 0;
}

