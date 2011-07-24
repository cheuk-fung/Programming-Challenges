/*
 *  SRC: POJ 3159
 * PROB: Candies
 * ALGO: Dijkstra
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::priority_queue;

const int MAX_N = 30010;

struct Edge
{
    int v, d;

    Edge(int _v, int _d)
        : v(_v), d(_d)
    { }

    bool operator < (const Edge& other) const
    {
        return d > other.d;
    }
};

struct Link {
    int v, d;
    Link* next;
};

Link buf[150010];
int buftail;
Link* edge[MAX_N];

int shortest[MAX_N + 1];

int dijkstra(int n)
{
    memset(shortest, 0x3f, sizeof(shortest));
    shortest[0] = 0;

    priority_queue<Edge> Q;
    Q.push(Edge(0, 0));
    
    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (d > shortest[u]) continue;
        Link* p = edge[u];
        while (p) {
            int v = p->v;
            int dis = p->d;
            if (dis + shortest[u] < shortest[v]) {
                shortest[v] = dis + shortest[u];
                Q.push(Edge(v, shortest[v]));
            }
            p = p->next;
        }
    }

    return shortest[n - 1];
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        u--; v--;

        if (!edge[u]) {
            edge[u] = &buf[buftail++];
            edge[u]->v = v;
            edge[u]->d = d;
        }
        else {
            buf[buftail].v = v;
            buf[buftail].d = d;
            buf[buftail].next = edge[u]->next;
            edge[u]->next = &buf[buftail++];
        }
    }

    printf("%d\n", dijkstra(n));

    return 0;
}

