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

const int MAX_V = 50010;
const int MAX_E = 100010;

long long dist[MAX_V];
int w[MAX_V];
bool vis[MAX_V];

struct Edge {
    int v, d;
    Edge *next;
};
Edge e_buf[MAX_E],
     *e_head[MAX_V],
     *e_tail = e_buf;

void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

void spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;

    queue<int> Q;
    Q.push(1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            int d = e->d;
            if (d + dist[u] < dist[v]) {
                dist[v] = d + dist[u];
                if (!vis[v]) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
}

void solve()
{
    int v, e;
    scanf("%d%d", &v, &e);

    for (int i = 1; i <= v; i++)
        scanf("%d", w + i);

    memset(e_buf, 0, sizeof(e_buf));
    memset(e_head, 0, sizeof(e_head));
    e_tail = e_buf;

    for (int i = 0; i < e; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a, b, c);
        add_edge(b, a, c);
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
