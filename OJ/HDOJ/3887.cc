/*
 *  SRC: HDOJ 3887
 * PROB: Counting Offspring
 * ALGO: BIT
 * DATE: May 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

class BIT {
    public:
        int c[MAXN];

        void reset() { memset(c, 0, sizeof(c)); }
        int lowbit(int x) { return x & -x; }
        void update(int x, int v) { for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ; }
        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

struct Edge {
    int v;
    Edge *next;
} e_buf[MAXN << 1], *e_head[MAXN], *e_tail;

struct Status {
    int u, father;
    Edge *e;
} s_buf[MAXN << 1], *s_top;

int ans[MAXN];

inline void add_edge(int u, int v)
{
    *e_tail = (Edge){v, e_head[u]};
    e_head[u] = e_tail++;
}

void getans(int root)
{
    s_top = s_buf;
    *++s_top = (Status){root, root, e_head[root]};
    while (s_top != s_buf) {
        int u = s_top->u;
        int father = s_top->father;
        Edge *e = s_top->e;
        s_top--;
        if (!ans[u]) {
            bit.update(u, 1);
            ans[u] = bit.sum(u);
        }
        for ( ; e; e = e->next) {
            if (e->v != father) {
                *++s_top = (Status){u, father, e->next};
                *++s_top = (Status){e->v, u, e_head[e->v]};
                break;
            }
        }
        if (!e) {
            ans[u] = bit.sum(u) - ans[u];
        }
    }
}

int main()
{
    int n, p;
    while (scanf("%d%d", &n, &p), n && p) {
        bit.reset();
        memset(ans, 0, sizeof(ans));
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }

        getans(p);
        for (int i = 1; i <= n; i++) {
            printf("%d%c", ans[i], i == n ? '\n' : ' ');
        }
    }

    return 0;
}

