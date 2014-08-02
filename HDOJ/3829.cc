/*
 *  SRC: HDOJ 3829
 * PROB: Cat VS Dog
 * ALGO: Hungarian
 * DATE: Apr 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 555;

bool edge[MAXN][MAXN];
int match[MAXN];
bool vis[MAXN];

bool find_path(int n, int u)
{
    for (int v = 0; v < n; v++) {
        if (edge[u][v] && !vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || find_path(n, match[v])) {
                match[v] = u;
                return true;
            }
        }
    }

    return false;
}

int hungarian(int n)
{
    int res = 0;
    memset(match,0xff, sizeof(match));
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        if (find_path(n, i)) res++;
    }

    return res;
}

int main()
{
    int n, m, p;
    while (~scanf("%d%d%d", &n, &m, &p)) {
        vector<int> like_cat[n], dislike_cat[n];
        vector<int> like_dog[m], dislike_dog[m];
        for (int i = 0; i < p; i++) {
            char which;
            int id;
            scanf(" %c%d", &which, &id);
            if (which == 'C') {
                like_cat[id - 1].push_back(i);
                scanf(" %*c%d", &id);
                dislike_dog[id - 1].push_back(i);
            } else {
                like_dog[id - 1].push_back(i);
                scanf(" %*c%d", &id);
                dislike_cat[id - 1].push_back(i);
            }
        }

        memset(edge, 0, sizeof(edge));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < like_cat[i].size(); j++) {
                for (int k = 0; k < dislike_cat[i].size(); k++) {
                    edge[like_cat[i][j]][dislike_cat[i][k]] = 1;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < dislike_dog[i].size(); j++) {
                for (int k = 0; k < like_dog[i].size(); k++) {
                    edge[dislike_dog[i][j]][like_dog[i][k]] = 1;
                }
            }
        }

        printf("%d\n", p - hungarian(p));
    }

    return 0;
}
