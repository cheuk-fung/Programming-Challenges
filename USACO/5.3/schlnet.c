/*
ID: os.idea1
LANG: C
TASK: schlnet
*/
#include <stdio.h>
#include <string.h>

#define MAX_N 111

FILE *fin, *fout;

struct Edge {
    int v;
    struct Edge *next;
};
struct Edge e_buf[MAX_N * MAX_N * 2],
            *buf_tail = e_buf,
            *orig_edge[MAX_N],
            *scc_edge[MAX_N];

inline void add_edge(struct Edge **e, int u, int v)
{
    buf_tail->v = v;
    buf_tail->next = e[u];
    e[u] = buf_tail++;
}

struct Stack {
    int a[MAX_N];
    int top;
} stack;

inline void stack_push_back(int p)
{
    stack.a[stack.top++] = p;
}

inline int stack_back()
{
    return stack.a[stack.top - 1];
}

inline void stack_pop_back()
{
    stack.top--;
}

int idx, scc_cnt;
int dfn[MAX_N], low[MAX_N], scc_id[MAX_N], scc_size[MAX_N];
int in_stack[MAX_N];

void tarjan_dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    in_stack[u] = 1;
    stack_push_back(u);

    struct Edge *e = orig_edge[u];
    while (e) {
        if (!dfn[e->v]) {
            tarjan_dfs(e->v);
            if (low[e->v] < low[u]) low[u] = low[e->v];
        }
        else if (in_stack[e->v])
            if (dfn[e->v] < low[u]) low[u] = dfn[e->v];
        e = e->next;
    }
    
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stack_back();
            stack_pop_back();
            in_stack[v] = 0;
            scc_id[v] = scc_cnt;
            scc_size[scc_cnt]++;
        } while (v != u) ;
    }
}

void tarjan(int n)
{
    idx = scc_cnt = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc_id, 0, sizeof(scc_id));
    memset(scc_size, 0, sizeof(scc_size));

    int i;
    for (i = 1; i <= n; i++)
        if (!dfn[i]) tarjan_dfs(i);
}

int ans_1, ans_2;
int fa[MAX_N], vis[MAX_N];

void solve(int n)
{
    if (scc_cnt == 1) {
        ans_1 = 1;
        return ;
    }

    int u;
    for (u = 1; u <= n; u++) {
        struct Edge *e = orig_edge[u];
        while (e) {
            if (scc_id[u] != scc_id[e->v]) {
                add_edge(scc_edge, scc_id[u], scc_id[e->v]);
                fa[scc_id[e->v]] = scc_id[u];
            }
            e = e->next;
        }
    }

    for (u = 1; u <= scc_cnt; u++) {
        if (!fa[u]) ans_1++;
        if (!scc_edge[u]) ans_2++;
    }

    if (ans_2 < ans_1) ans_2 = ans_1;
}

int main()
{
    fin = fopen("schlnet.in", "r");
    fout = fopen("schlnet.out", "w");

    int n;
    fscanf(fin, "%d", &n);

    int i;
    for (i = 1; i <= n; i++) {
        int j;
        while (fscanf(fin, "%d", &j), j) add_edge(orig_edge, i, j);
    }

    tarjan(n);
    solve(n);
    fprintf(fout, "%d\n%d\n", ans_1, ans_2);

    return 0;
}
