/*
 *  SRC: POJ 1639
 * PROB: Picnic Planning
 * ALGO: MST
 * DATE: Jul 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 100;

class Disjoint_Set {
    private:
        int a[MAXN];
    public:
        Disjoint_Set() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

struct Edge {
    int u, v, d;
    bool choose;

    Edge(int _u, int _v, int _d) : u(_u), v(_v), d(_d), choose(false) { }
    bool operator <(const Edge &o) const { return d < o.d; }
};
vector<Edge> e;

int idx;
map<string, int> name;
vector< pair<int, int> > park;
int mat[MAXN][MAXN];

int dfs(int u, int parent, int x, int y, int len)
{
    if (!u) {
        if (x != -1) {
            mat[x][y] = mat[y][x] = 0;
            return len;
        } else {
            return 0;
        }
    }

    for (int v = 0; v < idx; v++) {
        if (v != parent && mat[u][v]) {
            int tx = x, ty = y, tlen = len;
            if (mat[u][v] > tlen) {
                tlen = mat[u][v];
                tx = u;
                ty = v;
            }
            int r = dfs(v, u, tx, ty, tlen);
            if (r) return r;
        }
    }

    return 0;
}

int main()
{
    int n;
    cin >> n;

    name["Park"] = idx++;
    for (int i = 0; i < n; i++) {
        string u, v;
        int d;
        cin >> u >> v >> d;
        if (!name.count(u)) name[u] = idx++;
        if (!name.count(v)) name[v] = idx++;
        e.push_back(Edge(name[u], name[v], d));
    }

    int m;
    cin >> m;
    sort(e.begin(), e.end());

    int cnt = idx - 1;
    for (int i = 0; i < n; i++) {
        if (e[i].u && e[i].v && ds.find(e[i].u) != ds.find(e[i].v)) {
            ds.join(e[i].u, e[i].v);
            e[i].choose = true;
            cnt--;
            if (cnt == m) break;
        }
    }

    int degree = 0;
    for (int i = 0; i < n; i++) {
        if (!e[i].choose && ds.find(e[i].u) != ds.find(e[i].v)) {
            ds.join(e[i].u, e[i].v);
            e[i].choose = true;
            if (!e[i].u || !e[i].v) degree++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (e[i].choose) {
            mat[e[i].u][e[i].v] = mat[e[i].v][e[i].u] = e[i].d;
            ans += e[i].d;
        } else if (!e[i].u) {
            park.push_back(pair<int, int>(e[i].v, e[i].d));
        } else if (!e[i].v) {
            park.push_back(pair<int, int>(e[i].u, e[i].d));
        }
    }

    for (int i = 0; i < (int)park.size() && degree < m; i++) {
        int v = park[i].first;
        int d = park[i].second;
        int r = dfs(v, 0, -1, -1, d);
        if (r) {
            ans = ans - r + d;
            mat[0][v] = mat[v][0] = d;
            degree++;
        }
    }

    cout << "Total miles driven: " << ans << endl;

    return 0;
}

