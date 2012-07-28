#include <cstdio>
#include <vector>

using namespace std;

struct Edge {
    int v;
    int id;
    char c;

    Edge(int _v, int _id, char _c) : v(_v), id(_id), c(_c) { }
};
vector<Edge> mark[7];
int degree[7];
bool vis[110];
bool reachable[7];

void floodfill(int u)
{
    if (reachable[u]) return ;

    reachable[u] = true;
    for (int i = 0; i < (int)mark[u].size(); i++) {
        floodfill(mark[u][i].v);
    }
}

bool conn(int u)
{
    floodfill(u);
    for (int i = 0; i <= 6; i++) {
        if (degree[i] && !reachable[i]) return false;
    }
    return true;
}

void dfs(int u)
{
    for (int i = 0; i < (int)mark[u].size(); i++) {
        if (vis[mark[u][i].id]) continue;
        vis[mark[u][i].id] = true;
        dfs(mark[u][i].v);
        printf("%d %c\n", mark[u][i].id, mark[u][i].c);
    }
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        degree[l]++;
        degree[r]++;
        mark[l].push_back(Edge(r, i + 1, '-'));
        mark[r].push_back(Edge(l, i + 1, '+'));
    }

    int startmark;
    int oddmark;
    int oddcnt = 0;
    for (int i = 0; i <= 6; i++) {
        if (degree[i]) startmark = i;
        if (degree[i] & 1) {
            oddcnt++;
            oddmark = i;
        }
    }

    if (oddcnt > 2 || !conn(startmark)) puts("No solution");
    else dfs(oddcnt == 0 ? startmark : oddmark);

    return 0;
}
