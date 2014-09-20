#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100010;

class BIT {
    public:
        static const int bound = MAXN << 1;
        int c[bound];
        int lowbit(int x) { return x & -x; }
        void update(int x, int v)
        {
            for ( ; x < bound; c[x] += v, x += lowbit(x)) ;
        }
        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

class DisjointSet {
    public:
        int a[MAXN << 1];

        DisjointSet() { reset(); }
        void reset() { memset(a, 0xff, sizeof(a)); }

        int find(int u)
        {
            if (a[u] < 0) return u;
            return a[u] = find(a[u]);
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

typedef vector<int>::const_iterator vci;
typedef pair<int, int> pii;
vector<int> edge[MAXN];
vector<int> query[MAXN];
vector<pii> e;
int father[MAXN], dist[MAXN], ans[MAXN];
int idx, inidx[MAXN], outidx[MAXN];
bool vis[MAXN];

void tarjan(int u, int length)
{
    vis[u] = true;
    dist[u] = length;
    inidx[u] = idx--;

    for (vci v = query[u].begin(); v != query[u].end(); v++) {
        if (vis[*v]) {
            bit.update(inidx[u], 1);
            bit.update(inidx[*v], 1);
            bit.update(ds.find(inidx[*v]), -2);
        }
    }

    for (vci v = edge[u].begin(); v != edge[u].end(); v++) {
        if (*v != father[u]) {
            father[*v] = u;
            tarjan(*v, length + 1);
        }
    }

    ds.join(inidx[father[u]], inidx[u]);
    outidx[u] = idx--;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge[u - 1].push_back(v - 1);
        edge[v - 1].push_back(u - 1);
        e.push_back(pii(u - 1, v - 1));
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        query[u - 1].push_back(v - 1);
        query[v - 1].push_back(u - 1);
    }

    idx = 2 * n;
    father[0] = 0;
    tarjan(0, 0);

    for (int i = 0; i < e.size(); i++) {
        int x = (father[e[i].first] == e[i].second ? e[i].first : e[i].second);
        cout << bit.sum(inidx[x]) - bit.sum(outidx[x]) << " ";
    }

    return 0;
}

