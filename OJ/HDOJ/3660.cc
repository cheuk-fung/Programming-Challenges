/*
 *  SRC: HDOJ 3660
 * PROB: Alice and Bob's Trip
 * ALGO: Tree DP
 * DATE: Nov 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using std::max;
using std::min;

const int MAX_V = 500010;
const int INF   = 0x3f3f3f3f;

struct Edge {
    int v, d;
    Edge *next;
};
Edge e_buf[MAX_V],
     *e_head[MAX_V],
     *e_tail = e_buf;

int n, L, R;

inline void add_edge(int u, int v, int d)
{
    e_tail->v = v;
    e_tail->d = d;
    e_tail->next = e_head[u];
    e_head[u] = e_tail++;
}

int eval(int p, int curr, int is_bob)
{
    if (curr > R) return INF;
    if (!e_head[p]) return 0;

    int res = 0;
    if (!is_bob) res = INF;
    for (Edge *e = e_head[p]; e; e = e->next) {
        int next = eval(e->v, curr + e->d, is_bob ^ 1) + e->d;
        if (curr + next < L || curr + next > R) continue;
        if (is_bob) res = max(res, next);
        else res = min(res, next);
    }
    if (curr + res < L) res = INF;

    return res;
}

int next_int()
{
    char c;
    while (isspace(c = getchar()))
        ;
    int res = c - '0';
    while (isdigit(c = getchar())) {
        res = res * 10 + c - '0';
    }
    return res;
}

int main()
{
    while (scanf("%d%d%d", &n, &L, &R) != EOF) {
        memset(e_head, 0, sizeof(e_head));
        e_tail = e_buf;

        for (int i = 1; i < n; i++) {
            int u = next_int(), v = next_int(), d = next_int();
            add_edge(u, v, d);
        }

        int ans = eval(0, 0, 1);
        if (ans < INF) printf("%d\n", ans);
        else puts("Oh, my god!");
    }

    return 0;
}
