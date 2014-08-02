/*
 *  SRC: HDOJ 3666
 * PROB: THE MATRIX PROBLEM
 * ALGO: SPFA
 * DATE: Nov 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <deque>

using std::deque;

const int MAX_V = 810;
const int MAX_E = 500000;
const double eps = 1e-12;

inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

double dist[MAX_V];
bool vis[MAX_V];
int cnt[MAX_V];

struct Edge {
    int v;
    double d;
    Edge *next;
};
Edge e_buf[MAX_E],
     *e_head[MAX_V],
     *e_tail = e_buf;

void add_edge(int u, int v, double d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

bool spfa(int n)
{
    memset(vis, false, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n; i++) dist[i] = 1e100;
    dist[0] = 0.0;

    deque<int> que;
    double avg = 0.0;
    que.push_back(0);
    while (!que.empty()) {
        while (gr(dist[que.front()], avg)) {
            que.push_back(que.front());
            que.pop_front();
        }
        int u = que.front();
        double tot = avg * que.size() - dist[u];
        que.pop_front();

        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            double d = e->d;
            if (ls(d + dist[u], dist[v])) {
                dist[v] = d + dist[u];
                if (!vis[v]) {
                    if (++cnt[v] >= n) return false;
                    vis[v] = true;
                    tot += dist[v];
                    if (!que.empty() && ls(dist[v], dist[que.front()])) {
                        que.push_front(v);
                    } else {
                        que.push_back(v);
                    }
                }
            }
        }

        avg = tot / que.size();
    }

    return true;
}

int main()
{
    int n, m, l, u;
    while (~scanf("%d%d%d%d", &n, &m, &l, &u)) {
        memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                double c;
                scanf("%lf", &c);
                add_edge(i, j + n, -log(l / c));
                add_edge(j + n, i, log(u / c));
            }

        if (spfa(n + m)) puts("YES");
        else puts("NO");
    }

    return 0;
}
