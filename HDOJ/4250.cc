/*
 *  SRC: HDOJ 4250
 * PROB: A Famous King’s Trip
 * ALGO: GOD
 * DATE: Jul 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 200010;
const pii PII_INF = pii(INF, INF);

class Disjoint_Set {
    public:
        int a[MAXN];

        void reset(int n)
        {
            for (int i = 0; i < n; i++) a[i] = i;
        }

        int find(int u)
        {
            int x = u, y = u;
            while (a[u] != u) u = a[u];
            while (a[y] != y) {
                x = a[y];
                a[y] = u;
                y = x;
            }
            return u;
        }

        void join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (x != y) {
                a[x] = y;
            }
        }
};
Disjoint_Set ds;

struct Edge {
    int v;
    int idx;
    Edge *next;
};
Edge e_buf[MAXN << 1];
Edge *e_head[MAXN];
Edge *e_tail;

int n, m;
int degree[MAXN];
int odd[4];
int queue[MAXN];
bool vvis[MAXN], evis[MAXN];
bool is_candidate[MAXN];
pii candidate[MAXN];

inline void add_edge(int u, int v, int idx)
{
    *e_tail = (Edge){v, idx, e_head[u]};
    e_head[u] = e_tail++;
}

int find_edge(int u, int v)
{
    for (Edge *e = e_head[u]; e; e = e->next) {
        if (e->v == v) {
            return e->idx;
        }
    }
    return -1;
}

bool floodfill()
{
    memset(vvis, 0, sizeof vvis);
    int *head = queue, *tail = queue;
    *tail++ = 1;
    vvis[1] = true;

    while (head < tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next) {
            if (!vvis[e->v] && !evis[e->idx]) {
                *tail++ = e->v;
                vvis[e->v] = true;
                evis[e->idx] = true;
            }
        }
    }

    return tail - queue == n;
}

pii erase(pii r)
{
    memset(evis, 0, sizeof evis);
    evis[r.first] = evis[r.second] = true;
    if (floodfill()) return r;
    return PII_INF;
}

pii check(int a, int b, int c, int d)
{
    pii r;
    if ((r.first = find_edge(a, b)) == -1) return PII_INF;
    if ((r.second = find_edge(c, d)) == -1) return PII_INF;
    if (r.first > r.second) swap(r.first, r.second);
    return erase(r);
}

pii run()
{
    memset(degree, 0, sizeof degree);
    memset(e_head, 0, sizeof e_head);
    e_tail = e_buf;

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v, i);
        add_edge(v, u, i);
        degree[u]++;
        degree[v]++;
    }

    int odd_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) return PII_INF;
        if (degree[i] & 1) {
            if (degree[i] < 3) return PII_INF;
            if (odd_cnt == 4) return PII_INF;
            odd[odd_cnt++] = i;
        }
    }

    pii res = PII_INF;
    if (odd_cnt == 4) {
        res = min(res, check(odd[0], odd[1], odd[2], odd[3]));
        res = min(res, check(odd[0], odd[2], odd[1], odd[3]));
        res = min(res, check(odd[0], odd[3], odd[1], odd[2]));
    } else if (odd_cnt == 2) {
        memset(is_candidate, 0, sizeof is_candidate);
        for (int mid = 1; mid <= n; mid++) {
            if (mid == odd[0] || mid == odd[1]) continue;
            pii r;
            if ((r.first = find_edge(mid, odd[0])) == -1) continue;
            if ((r.second = find_edge(mid, odd[1])) == -1) continue;
            if (r.first > r.second) swap(r.first, r.second);
            is_candidate[mid] = true;
            candidate[mid] = r;
        }

        ds.reset(n + 1);
        memset(vvis, 0, sizeof vvis);
        memset(evis, 0, sizeof evis);
        for (int u = 1; u <= n; u++) {
            if (u == odd[0] || u == odd[1]) continue;
            for (Edge *e = e_head[u]; e; e = e->next) {
                if (e->v == odd[0]) vvis[u] = true;
                else if (e->v == odd[1]) evis[u] = true;
                else ds.join(u, e->v);
            }
        }

        memset(degree, 0, sizeof degree);
        for (int u = 1; u <= n; u++) {
            degree[ds.find(u)] += vvis[u] + evis[u];
        }

        for (int mid = 1; mid <= n; mid++) {
            if (is_candidate[mid] && degree[ds.find(mid)] > 2) {
                res = min(res, candidate[mid]);
            }
        }

        if (res != PII_INF) {
            res = erase(res);
        }
    }

    return res;
}

int main()
{
    for (int task = 1; ~scanf("%d%d", &n, &m); task++) {
        printf("Case %d: ", task);
        pii ans = run();
        if (ans != PII_INF) {
            puts("YES");
            printf("%d %d\n", ans.first, ans.second);
        } else {
            puts("NO");
        }
    }

    return 0;
}

