/*
 *  SRC: POJ 3692
 * PROB: Kindergarten
 * ALGO: Hungarian
 * DATE: Jul 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MAX_N = 209;

bool edge[MAX_N][MAX_N];

int g, b, m;

int match[MAX_N];
bool visited[MAX_N];

bool findPath(int u)
{
    for (int v = 1; v <= b; v++)
        if (edge[u][v] && !visited[v]) {
            visited[v] = true;
            int t = match[v];
            match[v] = u;
            if (t == -1 || findPath(t)) return true;
            match[v] = t;
        }
    return false;
}

int hungarian()
{
    int res = 0;
    memset(match, 0xff, sizeof(match));
    for (int i = 1; i <= g; i++) {
        memset(visited, 0, sizeof(visited));
        if (findPath(i)) res++;
    }
    return res;
}

bool buildGraph()
{

    scanf("%d%d%d", &g, &b, &m);
    if (!(g || b || m)) return false;

    memset(edge, true, sizeof(edge));
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x][y] = false;
    }

    return true;
}

int main()
{
    int CASE = 1;
    while (buildGraph())
        printf("Case %d: %d\n", CASE++, g + b -hungarian());

    return 0;
}

