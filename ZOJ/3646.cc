/*
 *  SRC: ZOJ 3646
 * PROB: Matrix Transformer
 * ALGO: Hungarian
 * DATE: Sep 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 209;

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
char mat[209][209];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%s", mat[i]);
        }

        for (int i = 0; i < n; i++) edge[i].clear();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 'U') {
                    edge[i].push_back(j);
                }
            }
        }
        int r = hungarian(n);
        puts(r == n ? "YES" : "NO");
    }

    return 0;
}

