/*
 *  SRC: HDOJ 4114
 * PROB: Disney's FastPass
 * ALGO: Dijkstra + DP
 * DATE: Sep 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int n, m, K;
int f[1 << 8][1 << 8][50];
int tag[50], ticket[50];
int T[50], FT[50];

struct Edge {
    int v, d;
    Edge *next;
};
Edge ebuf[5000];
Edge *ehead[50], *etail;

struct Node {
    int a, ticket, u;
    int tm;

    Node(int _a, int _ticket, int _u, int _tm) : a(_a), ticket(_ticket), u(_u), tm(_tm) { }
    bool operator<(const Node &o) const { return tm > o.tm; }
};

inline void addedge(int u, int v, int d)
{
    *etail = (Edge){v, d, ehead[u]};
    ehead[u] = etail++;
}

int dijkstra()
{
    priority_queue<Node> Q;
    Q.push(Node(0, 0, 0, 0));
    while (!Q.empty()) {
        Node top = Q.top();
        Q.pop();
        if (top.a + 1 == 1 << K && top.u == 0) return top.tm;
        if (f[top.a][top.ticket][top.u] < top.tm) continue;
        for (Edge *e = ehead[top.u]; e; e = e->next) {
            Node now(top.a, top.ticket | ticket[e->v], e->v, top.tm + e->d);
            if (now.tm < f[now.a][now.ticket][now.u]) {
                f[now.a][now.ticket][now.u] = now.tm;
                Q.push(now);
            }
            for (int i = 0; i < K; i++) {
                if (tag[e->v] & (1 << i)) {
                    now.a |= 1 << i;
                    now.ticket |= 1 << i;
                    if ((top.ticket | ticket[e->v]) & (1 << i)) {
                        now.tm += FT[i];
                        if (now.tm < f[now.a][now.ticket][now.u]) {
                            f[now.a][now.ticket][now.u] = now.tm;
                            Q.push(now);
                        }
                    } else {
                        now.tm += T[i];
                        if (now.tm < f[now.a][now.ticket][now.u]) {
                            f[now.a][now.ticket][now.u] = now.tm;
                            Q.push(now);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        etail = ebuf;
        memset(ehead, 0, sizeof ehead);
        memset(f, 0x7f, sizeof f);
        memset(tag, 0, sizeof tag);
        memset(ticket, 0, sizeof ticket);

        scanf("%d%d%d", &n, &m, &K);
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            u--; v--;
            addedge(u, v, d);
            addedge(v, u, d);
        }
        addedge(0, 0, 0);

        for (int i = 0; i < K; i++) {
            int p, ni;
            scanf("%d", &p);
            tag[--p] |= 1 << i;
            scanf("%d%d", T + i, FT + i);
            scanf("%d", &ni);
            for (int j = 0; j < ni; j++) {
                int v;
                scanf("%d", &v);
                ticket[v - 1] |= 1 << i;
            }
        }

        int r = dijkstra();
        printf("Case #%d: %d\n", task, r);
    }

    return 0;
}

