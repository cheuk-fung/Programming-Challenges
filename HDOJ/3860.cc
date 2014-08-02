/*
 *  SRC: HDOJ 3860
 * PROB: Circuit Board
 * ALGO: Dijkstra
 * DATE: Apr 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV = 250 * 250;
const int MAXE = MAXV * 10;
const long long INF = 0x3f3f3f3f3f3f3f3fll;
const int orig = 0, dest = MAXV - 1;

int r, c, p, o, q, k, w;
long long o_sum;
pair<int, int> power[250], output[250];
pair<int, int> fault[MAXV];
int graph[250][250][2];
int wire[10010];

struct Capacity {
    int x1, y1, x2, y2, m;
};
Capacity capa[MAXV * 2];

struct Edge {
    int v;
    long long d;
    Edge *next;

    bool operator<(const Edge &o) const
    {
        return d > o.d;
    }
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_tail;

long long dist[MAXV];

inline void add_edge(int u, int v, long long d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, d, e_head[v]};
    e_head[v] = e_tail++;
}

void dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<Edge> que;
    dist[orig] = 0;
    que.push((Edge){orig, 0, 0});

    while (!que.empty()) {
        int u = que.top().v;
        long long d = que.top().d;
        que.pop();
        if (d > dist[u]) continue;

        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            long long dis = e->d;
            if (dis + dist[u] < dist[v]) {
                dist[v] = dis + dist[u];
                que.push((Edge){v, dist[v], 0});
            }
        }
    }
}

bool check(int m)
{
    memset(e_head, 0, sizeof(e_head));
    e_tail = e_buf;

    for (int j = 0; j < c - 1; j++) {
        add_edge(orig, j + 1, min(m, graph[0][j][0]));
        add_edge((c - 1) * (r - 2) + j + 1, dest, min(m, graph[r - 1][j][0]));
    }

    if (p > 1) {
        add_edge(orig, r * c, power[0].second);
        for (int id = 1; id < p - 1; id++) {
            add_edge(r * c + id - 1, r * c + id, power[id].second);
        }
        add_edge(r * c + p - 2, dest, power[p - 1].second);
    } else {
        add_edge(orig, dest, power[0].second);
    }
    if (o > 1) {
        add_edge(orig, r * c + p, output[0].second);
        for (int id = 1; id < o - 1; id++) {
            add_edge(r * c + p + id - 1, r * c + p + id, output[id].second);
        }
        add_edge(r * c + p + o - 2, dest, output[o - 1].second);
    } else {
        add_edge(orig, dest, output[0].second);
    }

    for (int i = 0; i < power[0].first; i++) {
        add_edge(orig, i * (c - 1) + 1, min(m, graph[i][0][1]));
    }
    for (int id = 1; id < p; id++) {
        for (int i = power[id - 1].first; i < power[id].first; i++) {
            add_edge(r * c + id - 1, i * (c - 1) + 1, min(m, graph[i][0][1]));
        }
    }
    for (int i = power[p - 1].first; i < r - 1; i++) {
        add_edge(i * (c - 1) + 1, dest, min(m, graph[i][0][1]));
    }

    for (int i = 0; i < output[0].first; i++) {
        add_edge(orig, (i + 1) * (c - 1), min(m, graph[i][c - 1][1]));
    }
    for (int id = 1; id < o; id++) {
        for (int i = output[id - 1].first; i < output[id].first; i++) {
            add_edge(r * c + p + id - 1, (i + 1) * (c - 1), min(m, graph[i][c - 1][1]));
        }
    }
    for (int i = output[o - 1].first; i < r - 1; i++) {
        add_edge((i + 1) * (c - 1), dest, min(m, graph[i][c - 1][1]));
    }

    for (int i = 0; i < r - 1; i++) {
        for (int j = 0; j < c - 1; j++) {
            if (j + 1 != c - 1) {
                add_edge(i * (c - 1) + j + 1, i * (c - 1) + j + 2, min(m, graph[i][j + 1][1]));
            }
            if (i + 1 != r - 1) {
                add_edge(i * (c - 1) + j + 1, i * (c - 1) + j + c, min(m, graph[i + 1][j][0]));
            }
        }
    }

    dijkstra();

    return dist[dest] >= o_sum;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d%d", &r, &c);

        scanf("%d", &p);
        for (int i = 0; i < p; i++) {
            scanf("%d%d", &power[i].first, &power[i].second);
            power[i].first--;
        }
        sort(power, power + p);

        o_sum = 0;
        scanf("%d", &o);
        for (int i = 0; i < o; i++) {
            scanf("%d%d", &output[i].first, &output[i].second);
            output[i].first--;
            o_sum += output[i].second;
        }
        sort(output, output + o);

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%d%d%d%d%d", &capa[i].x1, &capa[i].y1, &capa[i].x2, &capa[i].y2, &capa[i].m);
            capa[i].x1--; capa[i].y1--;
            capa[i].x2--; capa[i].y2--;
        }

        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d%d", &fault[i].first, &fault[i].second);
            fault[i].first--; fault[i].second--;
        }

        scanf("%d", &w);
        for (int i = 0; i < w; i++) {
            scanf("%d", wire + i);
        }
        sort(wire, wire + w);
        wire[w] = 0x3f3f3f3f;

        for (int i = 0; i < q; i++) {
            if (capa[i].m < wire[0]) {
                capa[i].m = 0;
            } else {
                capa[i].m = *(upper_bound(wire, wire + w, capa[i].m) - 1);
            }
        }

        memset(graph, 0x3f, sizeof(graph));
        for (int i = 0; i < q; i++) {
            int x1 = capa[i].x1, y1 = capa[i].y1;
            int x2 = capa[i].x2, y2 = capa[i].y2;
            if (x1 == x2) {
                graph[x1][min(y1, y2)][0] = capa[i].m;
            } else {
                graph[min(x1, x2)][y1][1] = capa[i].m;
            }
        }

        for (int i = 0; i < k; i++) {
            int x = fault[i].first, y = fault[i].second;
            if (y > 0) graph[x][y - 1][0] = 0;
            if (y < c - 1) graph[x][y][0] = 0;
            if (x > 0) graph[x - 1][y][1] = 0;
            if (x < r - 1) graph[x][y][1] = 0;
        }

        int left = 0, right = w;
        while (left < right) {
            int mid = (left + right - 1) >> 1;
            if (check(wire[mid])) right = mid;
            else left = mid + 1;
        }

        if (left == w) {
            puts("-1");
        } else {
            printf("%d\n", wire[left]);
        }
    }

    return 0;
}

