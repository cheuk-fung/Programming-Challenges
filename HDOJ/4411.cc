/*
 *  SRC: HDOJ 4411
 * PROB: Arrest
 * ALGO: MCMF
 * DATE: Sep 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;
const int MAXV = 233;
const int MAXE = MAXV * MAXV << 2;

struct Edge {
    int v;
    int c, f; // capa, flow
    int cpf; // cost per flow
    Edge *next,
         *rev; // revese edge
};
Edge e_buf[MAXE],
     *e_tail,
     *e_head[MAXV];

struct Rnode {
    Rnode *next;
    Edge *which; // which edge
};
Rnode road[MAXV];
int que[MAXE], dist[MAXV];
bool vis[MAXV];

inline void add_edge(int u, int v, int c, int cpf)
{
    *e_tail = (Edge){v, c, 0, cpf, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, -cpf, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool spfa(int s, int t)
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    int *head = que,
        *tail = que;
    *tail++ = s;
    vis[s] = true;
    dist[s] = 0;
    road[s].next = 0;

    while (head != tail) {
        int u = *head++;
        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next)
            if (e->cpf + dist[u] < dist[e->v] && e->f < e->c) {
                dist[e->v] = e->cpf + dist[u];
                road[e->v].next = &road[u];
                road[e->v].which = e;
                if (vis[e->v] == false) {
                    vis[e->v] = true;
                    *tail++ = e->v;
                }
            }
    }

    return dist[t] < INF;
}

int flow(int t)
{
    int f = INF;
    for (Rnode *r = &road[t]; r->next; r = r->next)
        f = min(f, r->which->c - r->which->f);

    int res = 0;
    for (Rnode *r = &road[t]; r->next; r = r->next) {
        r->which->f += f;
        res += r->which->cpf;
        r->which->rev->f = -r->which->f;
    }
    res *= f;

    return res;
}

int mcmf(int s, int t)
{
    int res = 0;
    while (spfa(s, t)) res += flow(t);

    return res;
}

int mat[MAXV][MAXV];

void floyd(int n)
{
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (i == k) continue;
            for (int j = 0; j < n; j++) {
                if (j == k || j == i) continue;
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
}

int main()
{
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        memset(mat, INF, sizeof mat);
        for (int i = 0; i < m; i++) {
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);
            mat[x][y] = mat[y][x] = min(mat[x][y], d);
        }
        floyd(n + 1);

        int s = MAXV - 1, t = s - 1, tt = t - 1;
        int vs = tt - 1, vt = vs - 1;
        for (int i = 1; i <= n; i++) {
            // add_edge(i, i + n, INF, 0);
            add_edge(i, vt, 1, 0);
            add_edge(vs, i + n, 1, 0);
        }
        for (int i = 1; i <= n; i++) {
            add_edge(s, i, INF, mat[0][i]);
            add_edge(i + n, tt, INF, mat[i][0]);
            for (int j = i + 1; j <= n; j++) {
                add_edge(i + n, j, INF, mat[i][j]);
            }
        }
        add_edge(tt, t, k, 0);
        add_edge(t, s, INF, 0);

        printf("%d\n", mcmf(vs, vt));
    }

    return 0;
}
