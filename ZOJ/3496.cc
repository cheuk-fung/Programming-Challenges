/*
 *  SRC: ZOJ 3496
 * PROB: Assignment
 * ALGO: Network flow
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int INF = 0x3f3f3f3f;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 512;
const int MAXE = 100000;

struct Arc {
    int v;
    long long c, f;
    Arc *next, *rev;
};
Arc abuf[MAXE];
Arc *ahead[MAXV], *awork[MAXV], *atail;
int Q[MAXV], lev[MAXV];

inline long long MAX(long long x, long long y) { return x > y ? x : y; }
inline long long MIN(long long x, long long y) { return x < y ? x : y; }

inline void addedge(int u, int v, long long c)
{
    *atail = (Arc){v, c, 0, ahead[u]};
    ahead[u] = atail++;
    *atail = (Arc){u, 0, 0, ahead[v]};
    ahead[v] = atail++;
    ahead[u]->rev = ahead[v];
    ahead[v]->rev = ahead[u];
}

bool bfs(int s, int t)
{
    memset(lev, 0xff, sizeof lev);
    int *head = Q, *tail = Q;
    *tail++ = s;
    lev[s] = 0;

    while (head != tail) {
        int u = *head++;
        for (Arc *arc = ahead[u]; arc; arc = arc->next) {
            if (lev[arc->v] == -1 && arc->f < arc->c) {
                lev[arc->v] = lev[u] + 1;
                *tail++ = arc->v;
            }
        }
    }

    return lev[t] != -1;
}

long long dfs(int u, long long f, int t)
{
    if (u == t) return f;

    long long res = 0;
    for (Arc *&arc = awork[u]; arc; arc = arc->next) {
        if (lev[arc->v] == lev[u] + 1 && arc->f < arc->c) {
            long long ret = dfs(arc->v, MIN(f - res, arc->c - arc->f), t);
            res += ret;
            arc->f += ret;
            arc->rev->f = -arc->f;
            if (res == f) break;
        }
    }

    return res;
}

long long dinic(int s, int t)
{
    long long res = 0;
    while (bfs(s, t)) {
        memcpy(awork, ahead, sizeof ahead);
        long long ret = dfs(s, LLINF, t);
        if (ret == 0) break;
        res += ret;
    }
    return res;
}

int n, m, s, t, p;

struct Edge {
    int u, v, c;
} e[10010];

long long check_amin(int maxc)
{
    memset(ahead, 0, sizeof ahead);
    atail = abuf;

    for (int i = 0; i < m; i++) {
        addedge(e[i].u, e[i].v, MIN(e[i].c, maxc));
    }

    return dinic(s, t);
}

long long check_amax(int minc)
{
    memset(ahead, 0, sizeof ahead);
    atail = abuf;

    int vs = MAXV - 1, vt = vs - 1;
    for (int i = 0; i < m; i++) {
        addedge(e[i].u, e[i].v, e[i].c - minc);
        addedge(e[i].u, vt, minc);
        addedge(vs, e[i].v, minc);
    }
    addedge(t, s, LLINF);

    long long r = dinic(vs, vt);
    if (r != (long long)minc * m) return -1;
    return dinic(s, t);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d%d%d%d%d", &n, &m, &s, &t, &p);
        int maxc = 0, minc = INF;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
            maxc = MAX(maxc, e[i].c);
            minc = MIN(minc, e[i].c);
        }
        long long maxf = check_amin(maxc);
        if (minc == INF) minc = 0;

        int l = 0, r = maxc;
        while (l < r) {
            int mid = (l + r - 1) >> 1;
            if (check_amin(mid) == maxf) r = mid;
            else l = mid + 1;
        }
        printf("%lld ", (long long)l * p);

        l = 0, r = minc;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (check_amax(mid) == maxf) l = mid;
            else r = mid - 1;
        }
        printf("%lld\n", (long long)l * p);
    }

    return 0;
}

