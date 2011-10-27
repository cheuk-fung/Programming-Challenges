/*
 *  SRC: POJ 3013
 * PROB: Big Christmas Tree
 * ALGO: SPFA
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

const int MAX_N = 50010;

long long dist[MAX_N];
int w[MAX_N];
bool visited[MAX_N];

struct Link {
    int v, d;
    Link* next;
} buf[MAX_N << 2];
int buftail;
Link* edge[MAX_N];

void addEdge(int u, int v, int d)
{
    if (!edge[u]) {
        edge[u] = &buf[buftail++];
        edge[u]->v = v;
        edge[u]->d = d;
        edge[u]->next = 0;
    }
    else {
        buf[buftail].v = v;
        buf[buftail].d = d;
        buf[buftail].next = edge[u]->next;
        edge[u]->next = &buf[buftail++];
    }
}

void spfa()
{
    memset(visited, false, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;

    queue<int> Q;
    Q.push(1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        visited[u] = false;
        Link* p = edge[u];
        while (p) {
            int v = p->v;
            int d = p->d;
            if (d + dist[u] < dist[v]) {
                dist[v] = d + dist[u];
                if (!visited[v]) {
                    visited[v] = true;
                    Q.push(v);
                }
            }
            p = p->next;
        }
    }
}

void solve()
{
    int v, e;
    scanf("%d%d", &v, &e);

    for (int i = 1; i <= v; i++)
        scanf("%d", w + i);

    memset(edge, 0, sizeof(edge));
    buftail = 0;
    for (int i = 0; i < e; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    spfa();

    long long sum = 0;
    for (int i = 1; i <= v; i++) {
        if (dist[i] == dist[0]) {
            puts("No Answer");
            return ;
        }
        else sum += dist[i] * w[i];
    }
    
    printf("%lld\n", sum);
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) solve();

    return 0;
}
