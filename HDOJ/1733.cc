/*
 *  SRC: HDOJ 1733
 * PROB: Escape
 * ALGO: Network flow
 * DATE: Aug 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 66000 << 1;
const int MAXE = MAXV * 10;

struct Arc {
    int v, c, f;
    Arc *next, *rev;
};
Arc arcbuf[MAXE << 1];
Arc *archead[MAXV], *arcwork[MAXV], *arctail;
int que[MAXV], lev[MAXV];

void addarc(int u, int v, int c)
{
    *arctail = (Arc){v, c, 0, archead[u]};
    archead[u] = arctail++;
    *arctail = (Arc){u, 0, 0, archead[v]};
    archead[v] = arctail++;
    archead[u]->rev = archead[v];
    archead[v]->rev = archead[u];
}

bool bfs(int s, int t)
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = s;
    lev[s] = 0;
    while (head != tail) {
        int u = *head++;
        for (Arc *p = archead[u]; p; p = p->next) {
            if (lev[p->v] == -1 && p->f < p->c) {
                lev[p->v] = lev[u] + 1;
                *tail++ = p->v;
            }
        }
    }
    return lev[t] != -1;
}

int dfs(int u, int f, int t)
{
    if (u == t) return f;

    int res = 0;
    for (Arc *&p = arcwork[u]; p; p = p->next) {
        if (lev[p->v] == lev[u] + 1 && p->f < p->c) {
            int r = dfs(p->v, min(f - res, p->c - p->f), t);
            res += r;
            p->f += r;
            p->rev->f = -p->f;
            if (res == f) break;
        }
    }
    return res;
}

int dinic(int s, int t)
{
    int res = 0;
    while (bfs(s, t)) {
        memcpy(arcwork, archead, sizeof archead);
        int r = dfs(s, INF, t);
        if (!r) break;
        res += r;
    }
    return res;
}

int n, m, tmax;
char mat[20][20];
int rid[20][20];
const int s = MAXV - 1, t = s - 1;

inline int VIN(int x) { return x << 1; }
inline int VOUT(int x) { return x << 1 | 1; }

int run(int x)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '#') continue;

            int idx = (i * m + j) * tmax + x;
            addarc(VIN(idx), VOUT(idx), 1);
            if (i - 1 >= 0 && mat[i - 1][j] != '#') addarc(VOUT(idx), VIN(((i - 1) * m + j) * tmax + x - 1), INF);
            if (i + 1 <  n && mat[i + 1][j] != '#') addarc(VOUT(idx), VIN(((i + 1) * m + j) * tmax + x - 1), INF);
            if (j - 1 >= 0 && mat[i][j - 1] != '#') addarc(VOUT(idx), VIN((i * m + j - 1) * tmax + x - 1),   INF);
            if (j + 1 <  m && mat[i][j + 1] != '#') addarc(VOUT(idx), VIN((i * m + j + 1) * tmax + x - 1),   INF);

            if (mat[i][j] == 'X') addarc(rid[i][j], VIN(idx), INF);
            else if (mat[i][j] == '@') addarc(VOUT(idx), t, INF);
        }
    }

    int r = dinic(s, t);
    return r;
}

int main()
{
    while (~scanf("%d%d", &n, &m)) {
        memset(archead, 0, sizeof archead);
        arctail = arcbuf;

        for (int i = 0; i < n; i++) {
            scanf("%s", mat[i]);
        }

        tmax = n * m + 1;
        int xcnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'X') {
                    rid[i][j] = MAXV - 10 - xcnt++;
                    addarc(s, rid[i][j], 1);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == '@') {
                    int idx = (i * m + j) * tmax;
                    addarc(VIN(idx), VOUT(idx), 1);
                    addarc(VOUT(idx), t, 1);
                }
            }
        }

        int ans, flow = 0;
        for (ans = 1; ans <= n * m; ans++) {
            flow += run(ans);
            if (flow == xcnt) break;
        }

        printf("%d\n", ans == n * m + 1 ? -1 : ans);
    }

    return 0;
}

