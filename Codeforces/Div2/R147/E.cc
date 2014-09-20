#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

const int INF = 0x3f3f3f3f;
const int MAXV = 200;
const int MAXE = 100000;
const int orig = 0, dest = MAXV - 1, vdest = MAXV - 2;

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

bool spfa()
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));

    int *head = que,
        *tail = que;
    *tail++ = orig;
    vis[orig] = true;
    dist[orig] = 0;
    road[orig].next = 0;

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

    return dist[dest] < INF;
}

int flow()
{
    int f = INF;
    for (Rnode *r = &road[dest]; r->next; r = r->next)
        f = min(f, r->which->c - r->which->f);

    int res = 0;
    for (Rnode *r = &road[dest]; r->next; r = r->next) {
        r->which->f += f;
        res += r->which->cpf;
        r->which->rev->f = -r->which->f;
    }
    res *= f;

    return res;
}

int mcmf()
{
    int res = 0;
    while (spfa()) res += flow();

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    e_tail = e_buf;

    string t;
    cin >> t;

    int cnt[26];
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < SIZE(t); i++) {
        cnt[t[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        add_edge(orig, i + 1, cnt[i], 0);
    }

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        int m;
        cin >> s >> m;
        memset(cnt, 0, sizeof cnt);
        for (int j = 0; j < SIZE(s); j++) {
            cnt[s[j] - 'a']++;
        }
        for (int j = 0; j < 26; j++) {
            add_edge(j + 1, i + 30, cnt[j], i + 1);
        }
        add_edge(i + 30, vdest, m, 0);
    }
    add_edge(vdest, dest, INF, 0);

    int res = mcmf();
    if (e_head[dest]->rev->f == SIZE(t)) {
        cout << res << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}

