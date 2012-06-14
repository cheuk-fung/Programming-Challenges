/*
 *  SRC: HDOJ 3879
 * PROB: Base Station
 * ALGO: Dinic
 * DATE: Jun 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdarg>

using std::min;
using std::string;

inline void myscanf(string s, ...)
{
    va_list ap;
    va_start(ap, s);
#ifdef ONLINE_JUDGE
    int pos;
    while ((pos = s.find("lld")) != string::npos) {
        s.replace(pos, 3, "I64d");
    }
#endif
    vscanf(s.c_str(), ap);
}

inline void myprintf(string s, ...)
{
    va_list ap;
    va_start(ap, s);
#ifdef ONLINE_JUDGE
    int pos;
    while ((pos = s.find("lld")) != string::npos) {
        s.replace(pos, 3, "I64d");
    }
#endif
    vprintf(s.c_str(), ap);
}

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 100000;
const int MAXE = 1000000;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    long long c, f; // capa, flow
    Edge *next;
    Edge *rev; // revese edge
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, long long c)
{
    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;

    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next)
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }

    return lev[dest] > -1;
}

long long dfs(int u, long long f)
{
    if (u == dest) return f;

    long long res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            long long tmp = dfs(e->v, min(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (res == f) break;
        }

    return res;
}

long long dinic()
{
    long long res = 0;
    while (bfs()) {
        memcpy(e_work, e_head, sizeof(e_head));
        long long tmp = dfs(orig, LLINF);
        if (tmp) res += tmp;
        else break;
    }

    return res;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 1; i <= n; i++) {
            int p;
            scanf("%d", &p);
            add_edge(i, dest, p);
        }

        long long sum = 0;
        for (int i = 1; i <= m; i++) {
            int a, b;
            long long c;
            myscanf("%d%d%lld", &a, &b, &c);
            add_edge(orig, n + i, c);
            add_edge(n + i, a, LLINF);
            add_edge(n + i, b, LLINF);

            sum += c;
        }

        myprintf("%lld\n", sum - dinic());
    }

    return 0;
}

