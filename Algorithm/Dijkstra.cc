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

const int MAXN = ;

vector<Edge> edge[MAXN + 1];

int lowest[MAXN + 1];

int dijkstra()
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
            if (dis + lowest[u] < lowest[v]) {
                lowest[v] = dis + lowest[u];
                Q.push(Node(v, lowest[v]));
            }
        }
    }

    return something;
}

