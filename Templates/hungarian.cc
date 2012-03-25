/*
 *  SRC: POJ 3041
 * PROB: Asteroids
 * ALGO: Hungarian
 * DATE: Mar 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

const int MAXN = 555;

vector<int> edge[MAXN];
typedef vector<int>::const_iterator vci;

int match[MAXN];
bool vis[MAXN];

bool find_path(int u)
{
    for (vci v = edge[u].begin(); v != edge[u].end(); v++)
        if (!vis[*v]) {
            vis[*v] = true;
            if (match[*v] == -1 || find_path(match[*v])) {
                match[*v] = u;
                return true;
            }
        }

    return false;
}

int hungarian(int n)
{
    int res = 0;
    memset(match, 0xff, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if (find_path(i)) res++;
    }

    return res;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x - 1].push_back(y - 1);
    }
    printf("%d\n", hungarian(n));

    return 0;
}

