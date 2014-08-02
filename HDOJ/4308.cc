/*
 *  SRC: HDOJ 4308
 * PROB: Saving Princess claire_
 * ALGO: SPFA
 * DATE: Jul 22, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int>::const_iterator vci;
typedef vector<pii>::const_iterator vcpii;
const int MAXN = 5010;
const int INF = 0x3f3f3f3f;

vector<string> mat;
vector< vector<pii> > edge;
vector<int> trans;
vector<bool> istrans;
vector<int> dist;
vector<bool> inque;
queue<int> que;

char strbuf[MAXN];

int spfa(int orig, int dest)
{
    while (!que.empty()) que.pop();

    dist[orig] = 0;
    que.push(orig);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;

        if (istrans[u]) {
            for (vci v = trans.begin(); v != trans.end(); v++) {
                if (dist[*v] > dist[u]) {
                    dist[*v] = dist[u];
                    if (!inque[*v]) {
                        que.push(*v);
                        inque[*v] = true;
                    }
                }
            }
        }

        for (vcpii v = edge[u].begin(); v != edge[u].end(); v++) {
            if (dist[v->first] > dist[u] + v->second) {
                dist[v->first] = dist[u] + v->second;
                if (!inque[v->first]) {
                    que.push(v->first);
                    inque[v->first] = true;
                }
            }
        }
    }

    return dist[dest];
}

int main()
{
    int r, c, cost;
    while (~scanf("%d%d%d", &r, &c, &cost)) {
        dist.clear();
        mat.clear();
        edge.clear();
        trans.clear();
        istrans.clear();
        inque.clear();

        for (int i = 0; i < r; i++) {
            scanf("%s", strbuf);
            mat.push_back(strbuf);

            for (int j = 0; j < c; j++) {
                dist.push_back(INF);
                edge.push_back(vector<pii>());
                istrans.push_back(false);
                inque.push_back(false);
            }
        }

        int prince, princess;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                int idx = i * c + j;
                switch (mat[i][j]) {
                    case 'Y': prince = idx; break;
                    case 'C': princess = idx; break;
                    case 'P': trans.push_back(i * c + j); istrans[i * c + j] = true; break;
                    case '#': continue;
                }
                if (i > 0 && mat[i - 1][j] != '#') edge[idx].push_back(pii(((i - 1) * c + j), mat[i][j] == '*'));
                if (i + 1 < r && mat[i + 1][j] != '#') edge[idx].push_back(pii(((i + 1) * c + j), mat[i][j] == '*'));
                if (j > 0 && mat[i][j - 1] != '#') edge[idx].push_back(pii((i * c + j - 1), mat[i][j] == '*'));
                if (j + 1 < c && mat[i][j + 1] != '#') edge[idx].push_back(pii((i * c + j + 1), mat[i][j] == '*'));
            }
        }

        int res = spfa(prince, princess);
        if (res == INF) puts("Damn teoy!");
        else printf("%d\n", res * cost);
    }

    return 0;
}

