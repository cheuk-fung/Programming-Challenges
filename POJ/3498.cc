/*
 *  SRC: POJ 3498
 * PROB: March of the Penguins
 * ALGO: Dinic
 * DATE: Feb 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using std::min;
using std::vector;

const int INF = 0x3f3f3f3f,
          orig = 0,
          MAX_V = 220,
          MAX_E = 20000;
int dest;

struct Point {
    double x, y;
};
Point p[MAX_V];

inline double dist(const Point &a, const Point &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

struct Edge {
    int v;
    int c, f;
    Edge *next;
    Edge *rev;
};
Edge e_buf[MAX_E * 10],
     *e_tail,
     *e_head[MAX_V];

int que[MAX_V], lev[MAX_V];

inline void add_edge(int u, int v, int c)
{
    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

    int *head = que,
        *tail = que;
    *tail++ = orig;
    lev[orig] = 0;

    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next)
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }

    return lev[dest] > -1;
}

int dfs(int u, int f)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *e = e_head[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }

    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        int tmp = dfs(orig, INF);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        // memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        int n, tot = 0;
        double d;
        scanf("%d%lf", &n, &d);
        for (int i = 1; i <= n; i++) {
            int a, b;
            scanf("%lf%lf%d%d", &p[i].x, &p[i].y, &a, &b);
            tot += a;
            if (a) add_edge(orig, i * 2, a);
            add_edge(i * 2, i * 2 + 1, b);
        }

        d *= d;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (dist(p[i], p[j]) <= d) {
                    add_edge(i * 2 + 1, j * 2, INF);
                    add_edge(j * 2 + 1, i * 2, INF);
                }

        vector<int> ans;
        for (int i = 1; i <= n; i++) {
            dest = i * 2;
            if (dinic() == tot) ans.push_back(i - 1);
            for (Edge *e = e_buf; e != e_tail; e->f = 0, e++) ;
        }

        if (ans.size())
            for (int i = 0; i < ans.size(); i++)
                printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
        else puts("-1");
    }

    return 0;
}
