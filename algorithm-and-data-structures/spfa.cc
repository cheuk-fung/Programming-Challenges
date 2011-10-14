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
bool vis[MAX_N];

struct Link {
    int v, d;
    Link* next;
} edge_buf[MAX_N << 2];
Link *edge[MAX_N],
     *buf_tail = edge_buf;

void add_edge(int u, int v, int d)
{
    buf_tail->v = v;
    buf_tail->d = d;
    buf_tail->next = edge[u];
    edge[u] = buf_tail++;
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
        Link* p = edge[u];
        while (p) {
            int v = p->v;
            int d = p->d;
            if (d + dist[u] < dist[v]) {
                dist[v] = d + dist[u];
                if (!vis[v]) {
                    vis[v] = true;
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

    memset(edge_buf, 0, sizeof(edge_buf));
    memset(edge, 0, sizeof(edge));
    buf_tail = edge_buf;
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
