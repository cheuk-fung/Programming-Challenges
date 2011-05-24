/*
 *  SRC: POJ
 * TASK: Cell Phone Network
 * ALGO: Tree DP
 * DATE: 05/24/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

struct status {
    int u, i;

    status(int uu, int ii) : u(uu), i(ii) { }
};

stack<status> s;
vector<int> adj[20000], next[20000];
int f[20000][3];
bool visit[20000];

inline int min(int a, int b)
{
    return a < b ? a : b;
}

void dfs(int root)
{
    s.push(status(root, 0));
    while (!s.empty()) {
        int u = s.top().u, now = s.top().i;
        s.pop();

        visit[u] = true;

        bool flag = false;
        for (int i = now; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (visit[v]) continue;
            next[u].push_back(v);
            s.push(status(u, i + 1));
            s.push(status(v, 0));
            flag = true;
            break;
            /* dfs(v);
            f[u][0] += f[v][1];
            f[u][2] += min(f[v][0], min(f[v][1], f[v][2]));
            next.push_back(v);
            */
        }
        if (flag) continue;

        if (next[u].size() == 0) {
            f[u][1] = 20000;
            f[u][2] = 1;
            continue;
        }

        for (int i = 0; i < next[u].size(); i++) {
            int v = next[u][i];
            f[u][0] += f[v][1];
            f[u][1] += min(f[v][1], f[v][2]);
            f[u][2] += min(f[v][0], min(f[v][1], f[v][2]));
        }
        f[u][2]++;

        int r = f[u][1] - min(f[next[u][0]][1], f[next[u][0]][2]) + f[next[u][0]][2];
        for (int i = 1; i < next[u].size(); i++) {
            int v = next[u][i];
            int t = f[u][1] - min(f[v][1], f[v][2]) + f[v][2];
            r = min(r, t);
        }
        f[u][1] = r;
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    if (n == 1) {
        puts("0");
        return 0;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int root = 1;

    dfs(root);

    printf("%d\n", min(f[root][1], f[root][2]));

    return 0;
}

