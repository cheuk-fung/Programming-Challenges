/*
 *  SRC: POJ 3697
 * PROB: USTC campus network
 * ALGO: BFS
 * DATE: Sep 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

struct Elink {
    int v, next;
} link[1000010];
int l_end;

int n, m;
int head[10010];
int q[10010];
bool vis[10010], del[10010];

inline void del_edge(int u, int v)
{
    link[l_end].v = v;
    link[l_end].next = head[u];
    head[u] = l_end++;
}

bool work(int job)
{
    scanf("%d%d", &n, &m);
    if (!n && !m) return false;

    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    l_end = 1;

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        del_edge(a, b);
        del_edge(b, a);
    }

    int q_head = 0, q_tail = 0, ans = 0;
    q[q_tail++] = 1;
    vis[1] = true;
    while (q_head < q_tail) {
        int u = q[q_head++];
        ans++;
        memset(del, 0, sizeof(del));
        for (int p = head[u]; p; p = link[p].next)
            del[link[p].v] = true;
        for (int i = 2; i <= n; i++)
            if (!del[i] && !vis[i]) {
                q[q_tail++] = i;
                vis[i] = true;
            }
    }

    printf("Case %d: %d\n", job, ans - 1);

    return true;
}

int main()
{
    for (int jobs = 1; work(jobs); jobs++) ;

    return 0;
}
