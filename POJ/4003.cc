/*
 *  SRC: POJ 4003
 * PROB: Bob’s Race
 * ALGO: Monotone Priority Queue
 * DATE: Jul 20, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

struct Edge {
    int v, d;
    Edge *next;
};
Edge e_buf[MAXN << 1];
Edge *e_head[MAXN];
Edge *e_tail;

int n, m, q;
int root, maxlen, dsize;
int diameter[MAXN], tmp_diameter[MAXN];
int dis[MAXN];
int maxque[MAXN], minque[MAXN];
int maxqtime[MAXN], minqtime[MAXN];
int maxltime[MAXN], minltime[MAXN];

inline void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

int find_d(int u, int v)
{
    for (Edge *e = e_head[u]; e; e = e->next) {
        if (e->v == v) {
            return e->d;
        }
    }
    return -1;
}

void get_diameter(int u, int parent, int d, int len, int type)
{
    tmp_diameter[d] = u;
    bool is_leaf = true;
    for (Edge *e = e_head[u]; e; e = e->next) {
        if (e->v != parent) {
            is_leaf = false;
            get_diameter(e->v, u, d + 1, len + e->d, type);
        }
    }
    if (is_leaf) {
        if (len > maxlen) {
            maxlen = len;
            if (type == 0) {
                root = u;
            } else {
                dsize = d + 1;
                memcpy(diameter, tmp_diameter, sizeof(int) * dsize);
            }
        }
    }
}

void get_dis(int u, int len)
{
    dis[u] = len;
    for (Edge *e = e_head[u]; e; e = e->next) {
        if (dis[e->v] == -1) {
            get_dis(e->v, len + e->d);
        }
    }
}

int main()
{
    while (scanf("%d%d", &n, &m), n || m) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 1; i < n; i++) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            x--; y--;
            add_edge(x, y, z);
            add_edge(y, x, z);
        }

        maxlen = 0;
        get_diameter(0, -1, 0, 0, 0);

        maxlen = 0;
        dsize = 0;
        get_diameter(root, -1, 0, 0, 1);

        memset(dis, 0xff, sizeof(dis));
        dis[root] = dis[diameter[dsize - 1]] = 0;
        for (int i = 1; i < dsize - 1; i++) {
            int u = diameter[i - 1], v = diameter[i];
            dis[v] = dis[u] + find_d(u, v);
        }
        for (int i = dsize - 2, len = 0; i > 0; i--) {
            int u = diameter[i + 1], v = diameter[i];
            len += find_d(u, v);
            dis[v] = max(dis[v], len);
        }
        dis[root] = dis[diameter[dsize - 1]] = maxlen;

        for (int i = 0; i < dsize; i++) {
            int u = diameter[i];
            get_dis(u, dis[u]);
        }

        for (int i = 0; i < m; i++) {
            scanf("%d", &q);

            int len = 0;
            int maxqh = 0, maxqt = 0;
            int minqh = 0, minqt = 0;
            for (int i = 0; i < n; i++) {
                int ltime = -1;
                while (maxqh < maxqt && maxque[maxqt - 1] < dis[i]) {
                    maxqt--;
                    ltime = maxltime[maxqt];
                }
                maxque[maxqt] = dis[i];
                maxltime[maxqt] = ltime == -1 ? i : ltime;
                maxqtime[maxqt++] = i;

                ltime = -1;
                while (minqh < minqt && minque[minqt - 1] > dis[i]) {
                    minqt--;
                    ltime = minltime[minqt];
                }
                minque[minqt] = dis[i];
                minltime[minqt] = ltime == -1 ? i : ltime;
                minqtime[minqt++] = i;

                while (maxqh < maxqt && minqh < minqt && maxque[maxqh] - minque[minqh] > q) {
                    if (maxqtime[maxqh] < minqtime[minqh]) maxqh++;
                    else minqh++;
                }

                if (maxqh < maxqt && minqh < minqt && maxque[maxqh] - minque[minqh] <= q) {
                    len = max(len, i - max(maxltime[maxqh], minltime[minqh]) + 1);
                }
            }

            printf("%d\n", len);
        }
    }

    return 0;
}

