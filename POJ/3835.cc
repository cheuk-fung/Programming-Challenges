/*
 *  SRC: POJ 3835
 * PROB: Columbus's bargain
 * ALGO: SPFA
 * DATE: Nov 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using std::queue;

const int MAX_V = 50;
const int MAX_E = 5000;

int dist[MAX_V];
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
    dist[0] = 0;

    queue<int> Q;
    Q.push(0);
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

int init_p[MAX_V];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(e_buf, 0, sizeof(e_buf));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        int n, m;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int q, p;
            scanf("%d%d", &q, &p);
            init_p[q] = p;
            add_edge(0, q, p - 1);
        }

        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (init_p[i] == init_p[j]) {
                    add_edge(i, j, 0);
                    add_edge(j, i, 0);
                }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int a, b, p;
            scanf("%d%d%d", &a, &b, &p);
            add_edge(a, b, p);
        }

        spfa();

        for (int i = 1; i <= n; i++)
            printf("%d %d\n", i, dist[i]);

        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            bool flag = true;
            for (int j = 1; j <= n && flag; j++) {
                if (j == i) continue;
                for (int k = j + 1; k <= n && flag; k++) {
                    if (k == i) continue;
                    if (dist[i] == dist[j] + dist[k]) {
                        cnt++;
                        flag = false;
                    }
                }
            }
        }
        printf("%d\n", cnt);
    }

    return 0;
}
