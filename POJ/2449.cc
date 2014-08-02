/*
 *  SRC: POJ 2449
 * PROB: Remmarguts' Date
 * ALGO: The K-th SSSP
 * DATE: Jul 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAXV = 1010;
const int MAXE = 100010;

struct Edge {
    int v, d;
    Edge *next;

    bool operator <(const Edge &o) const { return d > o.d; }
};
Edge e_buf[MAXE << 1];
Edge *e_head[MAXV], *e_revhead[MAXV];
Edge *e_tail = e_buf;

int dist[MAXV];
int times[MAXV];

class Astar_Comparator {
    public:
        bool operator ()(const Edge &x, const Edge &y) const
        {
            return x.d + dist[x.v] > y.d + dist[y.v];
        }
};

priority_queue<Edge> dij_que;
priority_queue<Edge, vector<Edge>, Astar_Comparator> astar_que;

inline void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

inline void add_revedge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_revhead[u]};
    e_revhead[u] = e_tail++;
}

void dijkstra(int orig)
{
    memset(dist, 0x3f, sizeof dist);
    dist[orig] = 0;
    dij_que.push((Edge){orig, 0});
    while (!dij_que.empty()) {
        Edge u = dij_que.top();
        dij_que.pop();
        if (u.d > dist[u.v]) continue;
        for (Edge *e = e_revhead[u.v]; e; e = e->next) {
            if (u.d + e->d < dist[e->v]) {
                dist[e->v] = u.d + e->d;
                dij_que.push((Edge){e->v, dist[e->v]});
            }
        }
    }
}

int astar(int orig, int dest, int k)
{
    astar_que.push((Edge){orig, 0});
    while (!astar_que.empty()) {
        Edge u = astar_que.top();
        astar_que.pop();
        times[u.v]++;
        if (times[u.v] > k) continue;
        if (times[dest] == k) return u.d;
        for (Edge *e = e_head[u.v]; e; e = e->next) {
            astar_que.push((Edge){e->v, u.d + e->d});
        }
    }
    return -1;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        add_edge(u, v, d);
        add_revedge(v, u, d);
    }

    int s, t, k;
    scanf("%d%d%d", &s, &t, &k);
    if (s == t) k++;

    dijkstra(t);
    int r = astar(s, t, k);
    printf("%d\n", r);

    return 0;
}

