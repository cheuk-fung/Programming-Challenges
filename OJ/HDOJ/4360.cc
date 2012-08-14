/*
 *  SRC: HDOJ 4360
 * PROB: As long as Binbin loves Sangsang
 * ALGO: SSSP
 * DATE: Aug 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<long long, int> pii;

const long long INF = 0x3f3f3f3f3f3f3f3fll;

struct Node {
    int v;
    long long d;
    int kind, cnt;

    bool operator<(const Node &o) const { return d == o.d ? cnt < o.cnt : d > o.d; }
};

struct Edge {
    int v;
    long long d;
    int kind;
};
vector<Edge> e[1500];

inline int kind2num(char c)
{
    int r;
    switch (c) {
        case 'L': r = 0; break;
        case 'O': r = 1; break;
        case 'V': r = 2; break;
        case 'E': r = 3;
    }
    return r;
}

long long dist[1500][4];
int cnt[1500][4];

pii dijkstra(int s, int t)
{
    priority_queue<Node> q;
    memset(dist, 0x3f, sizeof dist);
    memset(cnt, 0, sizeof cnt);
    for (vector<Edge>::iterator it = e[s].begin(); it != e[s].end(); it++) {
        if (it->kind == 0) {
            q.push((Node){it->v, it->d, it->kind, 1});
            dist[it->v][it->kind] = it->d;
            cnt[it->v][it->kind] = 1;
        }
    }
    while (!q.empty()) {
        Node top = q.top();
        q.pop();
        if (top.d > dist[top.v][top.kind] || (top.d == dist[top.v][top.kind] && top.cnt < cnt[top.v][top.kind])) continue;
        for (vector<Edge>::iterator it = e[top.v].begin(); it != e[top.v].end(); it++) {
            if ((top.kind + 1) % 4 == it->kind && (top.d + it->d < dist[it->v][it->kind] || (top.d + it->d == dist[it->v][it->kind] && top.cnt + 1 > cnt[it->v][it->kind]))) {
                dist[it->v][it->kind] = top.d + it->d;
                cnt[it->v][it->kind] = top.cnt + 1;
                q.push((Node){it->v, top.d + it->d, it->kind, top.cnt + 1});
            }
        }
    }
    return pii(dist[t][3], cnt[t][3]);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case %d: ", task);

        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) e[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v, d;
            char kind;
            scanf("%d%d%d %c", &u, &v, &d, &kind);
            e[u].push_back((Edge){v, d, kind2num(kind)});
            e[v].push_back((Edge){u, d, kind2num(kind)});
        }

        pii r = dijkstra(1, n);
        if (r.first == INF) {
            puts("Binbin you disappoint Sangsang again, damn it!");
        } else {
            cout << "Cute Sangsang, Binbin will come with a donkey after travelling " << r.first << " meters and finding " << r.second / 4 << " LOVE strings at last." << endl;
        }
    }

    return 0;
}

