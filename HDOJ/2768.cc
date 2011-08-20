/*
 *  SRC: HDOJ 2768
 * PROB: Cat vs. Dog
 * ALGO: Hungarian
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>

using std::string;

const int MAX_N = 555;

bool edge[MAX_N][MAX_N];

int n, m;

int match[MAX_N];
bool visited[MAX_N];

bool findPath(int u)
{
    for (int v = 0; v < n; v++)
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
    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        if (findPath(i)) res++;
    }
    return res;
}

string like[MAX_N], dislike[MAX_N];

void buildGraph()
{

    int c, d;
    scanf("%d%d%d", &c, &d, &n);
    m = n;

    char buf[10];
    for (int i = 0; i < m; i++) {
        scanf("%s", buf);
        like[i] = buf;
        scanf("%s", buf);
        dislike[i] = buf;
    }

    memset(edge, false, sizeof(edge));
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++)
            if (like[i] == dislike[j] || dislike[i] == like[j])
                edge[i][j] = edge[j][i] = true;
    }
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        buildGraph();
        printf("%d\n", n - hungarian() / 2);
    }

    return 0;
}



