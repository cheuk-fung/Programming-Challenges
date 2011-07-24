/*
 *  SRC: POJ 3259
 * PROB: Wormholes
 * ALGO: Bellman Ford
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

struct Edge {
    int u, v, d;

    Edge(int _u, int _v, int _d)
        : u(_u), v(_v), d(_d)
    { }
};

const int MAX_N = 510;

int dist[MAX_N];
vector<Edge> edge;
typedef vector<Edge>::const_iterator vci;

bool bellmanFord()
{
    memset(dist, 0x3f, sizeof(dist));
    edge.clear();

    int n, m, w;
    scanf("%d%d%d", &n, &m, &w);

    for (int i = 0; i < m; i++) {
        int s, e, t;
        scanf("%d%d%d", &s, &e, &t);
        edge.push_back(Edge(s, e, t));
        edge.push_back(Edge(e, s, t));
    }
    for (int i = 0; i < w; i++) {
        int s, e, t;
        scanf("%d%d%d", &s, &e, &t);
        edge.push_back(Edge(s, e, -t));
    }
    
    dist[1] = 0;
    for (int i = 0; i < n - 1; i++)
        for (vci e = edge.begin(); e != edge.end(); e++)
            if (dist[e->v] > dist[e->u] + e->d)
                dist[e->v] = dist[e->u] + e->d;

    for (vci e = edge.begin(); e != edge.end(); e++)
        if (dist[e->v] > dist[e->u] + e->d)
            return true;

    return false;
}

int main()
{
    int F;
    scanf("%d", &F);

    while (F--) {
        if (bellmanFord()) puts("YES");
        else puts("NO");
    }

    return 0;
}
