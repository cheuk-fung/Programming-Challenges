#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 110;
const int INF = 0x3f3f3f3f;

struct Node {
    int v, d;

    Node(int _v, int _d) : v(_v), d(_d) { }

    bool operator <(const Node & o) const
    {
        return d > o.d;
    }
};

vector<int> edge[MAXN];
int dist[MAXN], revdist[MAXN];
long long cnt[MAXN][MAXN], revcnt[MAXN][MAXN];

void dijkstra(int n, int orig, int *dist, long long (*cnt)[MAXN])
{
    fill(dist + 1, dist + n + 1, INF);
    dist[orig] = 0;

    cnt[orig][0] = 1;
    priority_queue<Node> que;
    que.push(Node(orig, 0));
    while (!que.empty()) {
        Node u = que.top();
        que.pop();
        if (u.d > dist[u.v]) continue;
        for (int i = 0; i < (int)edge[u.v].size(); i++) {
            int v = edge[u.v][i];
            cnt[u.v][u.d] += cnt[v][u.d - 1];
            if (u.d + 1 < dist[v]) {
                dist[v] = u.d + 1;
                que.push(Node(v, dist[v]));
            }
        }
    }
}

int main(int argc, char *args[])
{
    int n, m;
    cin >> n >>m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    dijkstra(n, 1, dist, cnt);
    dijkstra(n, n, revdist, revcnt);

    double ans = 1.0;
    long long tot = cnt[n][dist[n]];
    for (int i = 2; i < n; i++) {
        if (dist[i] + revdist[i] == dist[n]) {
            double now = cnt[i][dist[i]] * revcnt[i][revdist[i]] * 2.0 / tot;
            if (now - 1e-8 > ans) {
                ans = now;
            }
        }
    }

    cout.precision(10);
    cout << ans << endl;

    return 0;
}

