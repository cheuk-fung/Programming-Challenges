/*
 *  SRC: POJ 1201
 * PROB: Intervals
 * ALGO: SPFA(max)
 * DATE: Jul 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

const int MAX_N = 50010;

struct Link {
    int v, d;
    Link* next;
} buf[MAX_N * 10];
int buftail;

Link* edge[MAX_N];

queue<int> Q;

bool visited[MAX_N];
int dist[MAX_N];

void addEdge(int u, int v, int d)
{
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

void spfa()
{
    for (int i = 0; i < MAX_N; i++)
        dist[i] = -0x3FFFFFFF;

    dist[0] = 0;
    Q.push(0);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        visited[u] = false;
        Link* p = edge[u];
        while (p) {
            int v = p->v;
            int dis = p->d;
            if (dis + dist[u] > dist[v]) {
                dist[v] = dis + dist[u];
                if (!visited[v]) {
                    visited[v] = true;
                    Q.push(v);
                }
            }
            p = p->next;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int maxNum = 0;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b + 1, c);
        if (b + 1 > maxNum) maxNum = b + 1;
    }

    for (int i = 0; i <= maxNum; i++) {
        addEdge(i, i + 1, 0);
        addEdge(i + 1, i, -1);
    }

    spfa();

    printf("%d\n", dist[maxNum]);

    return 0;
}

