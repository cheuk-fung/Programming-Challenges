/*
 *  SRC: POJ 2396
 * PROB: Budget
 * ALGO: Network flow
 * DATE: Aug 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 10000;
const int MAXE = MAXV * 200;

struct Edge {
    int v, c, f;
    Edge *next, *rev;
};
Edge ebuf[MAXE];
Edge *ehead[MAXV], *ework[MAXV], *etail;
int que[MAXV], lev[MAXV];

inline void addedge(int u, int v, int c)
{
    *etail = (Edge){v, c, 0, ehead[u]};
    ehead[u] = etail++;
    *etail = (Edge){u, 0, 0, ehead[v]};
    ehead[v] = etail++;
    ehead[u]->rev = ehead[v];
    ehead[v]->rev = ehead[u];
}

bool bfs(int orig, int dest)
{
    memset(lev, 0xff, sizeof lev);

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;
    while (head != tail) {
        int u = *head++;
        for (Edge *e = ehead[u]; e; e = e->next) {
            if (lev[e->v] == -1 && e->f < e->c) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
        }
    }
    return lev[dest] != -1;
}

int dfs(int u, int f, int dest)
{
    if (u == dest) return f;

    int res = 0;
    for (Edge *&e = ework[u]; e; e = e->next) {
        if (lev[e->v] == lev[u] + 1 && e->f < e->c) {
            int r = dfs(e->v, min(f - res, e->c - e->f), dest);
            res += r;
            e->f += r;
            e->rev->f = -e->f;
            if (res == f) break;
        }
    }
    return res;
}

int dinic(int orig, int dest)
{
    int res = 0;
    while (bfs(orig, dest)) {
        memcpy(ework, ehead, sizeof ehead);
        int r = dfs(orig, INF, dest);
        if (!r) break;
        res += r;
    }
    return res;
}

int row[201], col[21];
bool equ[201][21];
int base[201][21];
int capa[201][21];

bool change(int r, int c, char s, int v)
{
    if (s == '<') {
        capa[r][c] = min(capa[r][c], v - 1);
    } else if (s == '>') {
        base[r][c] = max(base[r][c], v + 1);
    } else {
        if (equ[r][c] && capa[r][c] != v) return true;
        if (capa[r][c] != INF && capa[r][c] < v) return true;
        if (base[r][c] != -1 && base[r][c] > v) return true;
        base[r][c] = capa[r][c] = v;
        equ[r][c] = 1;
    }

    return false;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(equ, 0, sizeof equ);
        memset(base, 0xff, sizeof base);
        memset(capa, 0x3f, sizeof capa);

        int m, n;
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= m; i++) scanf("%d", row + i);
        for (int i = 1; i <= n; i++) scanf("%d", col + i);

        int c;
        scanf("%d", &c);
        bool impossible = false;
        for (int i = 0; i < c; i++) {
            int r, q, v;
            char s;
            scanf("%d%d %c%d", &r, &q, &s, &v);
            if (r == 0 && q == 0) {
                for (int i = 1; i <= m; i++) {
                    for (int j = 1; j <= n; j++) {
                        impossible |= change(i, j, s, v);
                    }
                }
            } else if (r == 0) {
                for (int i = 1; i <= m; i++) {
                    impossible |= change(i, q, s, v);
                }
            } else if (q == 0) {
                for (int i = 1; i <= n; i++) {
                    impossible |= change(r, i, s, v);
                }
            } else {
                impossible |= change(r, q, s, v);
            }
        }
        if (impossible) {
            puts("IMPOSSIBLE");
        } else {
            memset(ehead, 0, sizeof ehead);
            etail = ebuf;
            int sum = 0;
            int orig = MAXV - 2, dest = MAXV - 1;
            int vorig = MAXV - 4, vdest = MAXV - 3;
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    if (base[i][j] == -1) base[i][j] = 0;
                    int idx = (i - 1) * n + j - 1;
                    addedge(idx << 1, idx << 1 | 1, capa[i][j] - base[i][j]);
                    addedge(idx << 1, vdest, base[i][j]);
                    addedge(vorig, idx << 1 | 1, base[i][j]);
                    sum += base[i][j];
                }
            }

            for (int i = 1; i <= m; i++) {
                int rid = m * n * 2 + i;
                addedge(orig, vdest, row[i]);
                addedge(vorig, rid, row[i]);
                sum += row[i];
                for (int j = 1; j <= n; j++) {
                    int idx = (i - 1) * n + j - 1;
                    addedge(rid, idx << 1, INF);
                }
            }
            for (int j = 1; j <= n; j++) {
                int cid = m * n * 2 + m + j;
                addedge(cid, vdest, col[j]);
                addedge(vorig, dest, col[j]);
                sum += col[j];
                for (int i = 1; i <= m; i++) {
                    int idx = (i - 1) * n + j - 1;
                    addedge(idx << 1 | 1, cid, INF);
                }
            }
            addedge(dest, orig, INF);

            int r = dinic(vorig, vdest);
            if (r != sum) {
                puts("IMPOSSIBLE");
            } else {
                Edge *e = ebuf;
                for (int i = 1; i <= m; i++) {
                    for (int j = 1; j <= n; j++, e += 6) {
                        printf("%d%c", base[i][j] + e->f, j == n ? '\n' : ' ');
                    }
                }
            }
        }
        if (tasks) putchar(10);
    }

    return 0;
}

