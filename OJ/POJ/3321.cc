/*
 *  SRC: POJ 3321
 * PROB: Apple Tree
 * ALGO: BIT
 * DATE: Jul 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

class BIT
{
    public:
        int c[MAXN];
        int lowbit(int x) { return x & -x; }
        void update(int x, int v) {
            for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ;
        }
        int sum(int x) {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

struct Edge {
    int v;
    Edge *next;
};
Edge e_buf[MAXN << 2];
Edge *e_head[MAXN];
Edge *e_tail = e_buf;

int idx, dfn[MAXN], max_son[MAXN];
int apple[MAXN];

inline void add_edge(int u, int v)
{
    *e_tail = (Edge){v, e_head[u]};
    e_head[u] = e_tail++;
}

int build(int u, int parent)
{
    max_son[u] = dfn[u] = idx++;

    for (Edge *e = e_head[u]; e; e = e->next) {
        if (e->v == parent) continue;
        max_son[u] = max(max_son[u], build(e->v, u));
    }

    return max(dfn[u], max_son[u]);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        apple[i] = 1;
        bit.update(i, 1);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    idx = 1;
    max_son[1] = build(1, 0);

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        char c;
        int x;
        scanf(" %c%d", &c, &x);
        if (c == 'Q') {
            printf("%d\n", bit.sum(max_son[x]) - bit.sum(dfn[x] - 1));
        } else {
            bit.update(dfn[x], apple[x] *= -1);
        }
    }

    return 0;
}

