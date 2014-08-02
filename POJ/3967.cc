/*
 *  SRC: POJ 3967
 * PROB: Ideal Path
 * ALGO: SPFA
 * DATE: Oct 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

const int MAX_N = 100010,
          MAX_M = 200010;

struct Edge {
    int v, id;
    Edge *next;
} buf[MAX_M * 10];
Edge *e[MAX_N],
     *buf_tail = buf;

int n, m, l;
int ans[MAX_N];
vector<int> p1, p2;
vector<int> *curr = &p1, *next = &p2;

int dist_start[MAX_N], dist_end[MAX_N];
int vis[MAX_N];

int q[MAX_M * 10];

void add_edge(int u, int v, int id)
{
    buf_tail->v = v;
    buf_tail->id = id;
    buf_tail->next = e[u];
    e[u] = buf_tail++;
}

void spfa(int s, int *dist)
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(int) * MAX_N);
    dist[s] = 0;

    int q_head = 0, q_tail = 0;
    q[q_tail++] = s;
    while (q_head < q_tail) {
        int u = q[q_head++];

        vis[u] = false;
        Edge *p = e[u];
        while (p) {
            int v = p->v;
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                if (!vis[v]) {
                    vis[v] = true;
                    q[q_tail++] = v;
                }
            }
            p = p->next;
        }
    }
}

void get_ans()
{
    memset(vis, 0, sizeof(vis));
    int vis_id = 0;
    for (int d = 1; d <= l; d++) {
        int min_id = 0x3fffffff;
        for (int i = 0; i < curr->size(); i++) {
            int u = (*curr)[i];
            Edge *p = e[u];
            while (p) {
                int v = p->v,
                    id = p->id;
                if (dist_start[v] == d && dist_end[v] == l - d) {
                    if (id < min_id) {
                        min_id = id;
                        next->clear();
                        next->push_back(v);

                        vis_id++;
                        vis[v] = vis_id;
                    }
                    else if (id == min_id && vis[v] != vis_id) {
                        next->push_back(v);
                        vis[v] = vis_id;
                    }
                }
                p = p->next;
            }
        }

        ans[d] = min_id;

        vector<int> *t = curr;
        curr = next;
        next = t;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, id;
        scanf("%d%d%d", &u, &v, &id);
        if (u == v) continue;

        add_edge(u, v, id);
        add_edge(v, u, id);
    }

    spfa(1, dist_start);
    spfa(n, dist_end);

    l = dist_start[n];
    curr->push_back(1);
    get_ans();

    printf("%d\n", l);
    for (int i = 1; i < l; i++) printf("%d ", ans[i]);
    printf("%d\n", ans[l]);

    return 0;
}
