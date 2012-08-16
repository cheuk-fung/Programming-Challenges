#include <cassert>
#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;
const int MAXN = 10000;

map<pii, int> pnt;
vector<pii> edge[MAXN];
vector<pii> ver;
bool vis[MAXN];

inline int cross(const pii &base, const pii &a, const pii &b)
{
    int r = (a.first - base.first) * (b.second - base.second) - (a.second - base.second) * (b.first - base.first);
    if (r > 0) return 1;
    if (r < 0) return -1;
    return 0;
}

inline int dot(const pii &base, const pii &a, const pii &b)
{
    return (a.first - base.first) * (b.first - base.first) + (a.second - base.second) * (b.second - base.second);
}

inline double length(const pii &a, const pii &b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

string check(pii p, int n)
{
    for (int i = 0; i < n; i++) {
        int x0 = ver[i].first, x1 = ver[(i + 1) % n].first;
        int y0 = ver[i].second,y1 = ver[(i + 1) % n].second;
        if (x0 > x1) swap(x0, x1);
        if (y0 > y1) swap(y0, y1);
        if (x0 <= p.first && p.first <= x1 && y0 <= p.second && p.second <= y1 && cross(ver[i], ver[(i + 1) % n], p) == 0) return "BORDER";
    }

    double angle = 0.0;
    for (int i = 0; i < n; i++) {
        angle += cross(p, ver[i], ver[(i + 1) % n]) * acos(dot(p, ver[i], ver[(i + 1) % n]) / (length(p, ver[i]) * length(p, ver[(i + 1) % n])));
    }

    if (fabs((fabs(angle) - 2 * acos(-1.0))) < 1e-6) return "INSIDE";
    return "OUTSIDE";
}

void dfs(int u)
{
    for (int i = 0; i < (int)edge[u].size(); i++) {
        int idx = pnt[edge[u][i]];
        if (vis[idx]) continue;
        vis[idx] = true;
        dfs(idx);
        ver.push_back(edge[u][i]);
    }
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    int idx = 0;
    for (int i = 0; i < n; i++) {
        pii a, b;
        scanf("%d%d%d%d", &a.first, &a.second, &b.first, &b.second);
        if (!pnt.count(a)) pnt[a] = idx++;
        if (!pnt.count(b)) pnt[b] = idx++;
        edge[pnt[a]].push_back(b);
        edge[pnt[b]].push_back(a);
    }

    dfs(0);

    int x, y;
    scanf("%d%d", &x, &y);
    puts(check(pii(x, y), n).c_str());

    return 0;
}
