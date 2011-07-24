/*
 *  SRC: NKOJ p1838
 * PROB: Silver Cow Party
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

const int MAX_N = 1010;

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

int n, m, x;
int map[MAX_N][MAX_N], sum[MAX_N];
int shortest[MAX_N + 1];

void dijkstra()
{
    memset(shortest, 0x3f, sizeof(shortest));
    shortest[x] = 0;

    priority_queue<Edge> Q;
    Q.push(Edge(x, shortest[x]));
    
    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (d > shortest[u]) continue;
        for (int v = 1; v <= n; v++)
            if (map[u][v]) {
                int dis = map[u][v];
                if (dis + shortest[u] < shortest[v]) {
                    shortest[v] = dis + shortest[u];
                    Q.push(Edge(v, shortest[v]));
                }
            }
    }

    for (int i = 1; i <= n; i++) sum[i] += shortest[i];
}

void reverse()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++) {
            int t = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = t;

        }
}

int main()
{
    scanf("%d%d%d", &n, &m, &x);

    memset(map, 0x3f, sizeof(map));
    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        if (t < map[a][b]) map[a][b] = t;
    }
        
    dijkstra();
    reverse();
    dijkstra();

    int max = 0;
    for (int i = 1; i <= n; i++)
        if (max < sum[i]) max = sum[i];

    printf("%d\n", max);

    return 0;
}



