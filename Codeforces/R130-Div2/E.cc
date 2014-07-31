#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int MAXN = 100010;

vector<int> tree[MAXN];
vector<int> lev[MAXN];
vector<int> levdfn[MAXN << 1];
pair<int, int> dfn[MAXN];
int times;
int anc[MAXN];
int dep[MAXN];

void traverse(int u, int d)
{
    dfn[u].first = times++;

    dep[u] = d;
    lev[d].push_back(u);
    levdfn[d].push_back(dfn[u].first);
    for (int i = 0; i < (int)tree[u].size(); i++) {
        traverse(tree[u][i], d + 1);
    }

    dfn[u].second = times++;
    levdfn[d].push_back(dfn[u].second);
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> anc[i];
        tree[anc[i]].push_back(i);
    }

    traverse(0, 0);

    int m;
    cin >> m;
    while (m--) {
        int v, p;
        cin >> v >> p;
        if (dep[v] <= p) {
            cout << 0 << endl;
        } else {
            int ancdep = dep[v] - p;
            vector<int>::const_iterator it = upper_bound(levdfn[ancdep].begin(), levdfn[ancdep].end(), dfn[v].second);
            cout << (upper_bound(levdfn[dep[v]].begin(), levdfn[dep[v]].end(), *it) - lower_bound(levdfn[dep[v]].begin(), levdfn[dep[v]].end(), *(it - 1))) / 2 - 1 << endl;
        }
    }

    return 0;
}

