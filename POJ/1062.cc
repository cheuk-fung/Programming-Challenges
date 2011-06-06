/*
 *  SRC: POJ
 * TASK: 昂贵的聘礼
 * ALGO: Dijkstra
 * DATE: 06/05/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;

struct Edge
{
    int v, d;

    Edge(int vv, int dd)
        : v(vv), d(dd)
    { }
};

struct Node : public Edge
{
    Node(int vv, int dd)
        : Edge(vv, dd)
    { }

    bool operator < (const Node& other) const
    {
        return d > other.d;
    }
};

const int MAXN = 200;

vector<Edge> edge[MAXN + 1];

int lowest[MAXN + 1];

int m, n;
int P[MAXN + 1], L[MAXN + 1];

int dijkstra(int botLev, int topLev)
{
    memset(lowest, 0x3f, sizeof(lowest));
    lowest[0] = 0;

    priority_queue<Node> Q;
    Q.push(Node(0, 0));
    
    while (!Q.empty()) {
        int u = Q.top().v;
        int d = Q.top().d; 
        Q.pop();
        if (d > lowest[u]) continue;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v;
            int dis = edge[u][i].d;
            if (!(botLev <= L[v] && L[v] <= topLev)) continue;
            if (dis + lowest[u] < lowest[v]) {
                lowest[v] = dis + lowest[u];
                Q.push(Node(v, lowest[v]));
            }
        }
    }

    int ans = 0x7fffffff;
    for (int i = 0; i < n; i++) {
        if (lowest[i] + P[i] < ans) ans = lowest[i] + P[i];
    }

    return ans;
}

int main()
{
    scanf("%d%d", &m, &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d%d%d", P + i, L + i, &x);
        for (int j = 0; j < x; j++) {
            int t, v;
            scanf("%d%d", &t, &v);
            t--;
            edge[i].push_back(Edge(t, v));
        }
    }

    int ans = 0x7fffffff;
    for (int i = L[0] - m; i <= L[0]; i++) {
        int now = dijkstra(i, i + m);
        if (now < ans) ans = now;
    }

    printf("%d\n", ans);

    return 0;
}
