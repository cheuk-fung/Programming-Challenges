#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;

template<class T> inline int SIZE(const T &x) { return x.size(); }

vector<pii> e[MAXN];
vector<int> other[MAXN];
map<int, int> next[MAXN];

int dist[MAXN];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        e[a].push_back(pii(b, c));
        e[b].push_back(pii(a, c));
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            other[i].push_back(t);
        }
        for (int j = k - 1; j >= 0; j--) {
            if (binary_search(other[i].begin(), other[i].end(), other[i][j] + 1)) {
                next[i][other[i][j]] = next[i][other[i][j] + 1];
            } else {
                next[i][other[i][j]] = other[i][j] + 1;
            }
        }
    }

    memset(dist, 0x3f, sizeof dist);
    priority_queue<pii> Q;
    Q.push(pii(0, 0));
    dist[0] = 0;
    while (!Q.empty()) {
        int u = Q.top().first, d = Q.top().second;
        Q.pop();
        if (d > dist[u]) continue;
        if (binary_search(other[u].begin(), other[u].end(), d)) {
            d = next[u][d];
        }
        for (int i = 0; i < SIZE(e[u]); i++) {
            int v = e[u][i].first, now = d + e[u][i].second;
            if (now < dist[v]) {
                dist[v] = now;
                Q.push(pii(v, now));
            }
        }
    }

    cout << (dist[n - 1] == INF ? -1 : dist[n - 1]) << endl;

    return 0;
}

