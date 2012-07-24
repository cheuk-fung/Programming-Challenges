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
int pos[MAXN];

class Comparator {
    private:
        int p;
    public:
        Comparator(int _p) : p(_p) { }
        bool operator ()(int x, int y) const
        {
            int ancdep = dep[x] - p;
            vector<int>::const_iterator it = upper_bound(levdfn[ancdep].begin(), levdfn[ancdep].end(), max(dfn[x].second, dfn[y].second));
            return !(*(it - 1) < min(dfn[x].first, dfn[y].first));
            /*
            for (int i = 0; i < p; i++) {
                x = anc[x];
                y = anc[y];
                if (x == y) return false;
            }
            return true;
            */
        }
};

void traverse(int u, int d)
{
    dfn[u].first = times++;

    dep[u] = d;
    pos[u] = lev[d].size();
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
            cout << upper_bound(lev[dep[v]].begin() + pos[v] + 1, lev[dep[v]].end(), v, Comparator(p)) - lower_bound(lev[dep[v]].begin(), lev[dep[v]].begin() + pos[v] + 1, v, Comparator(p)) - 1 << endl;
        }
    }

    return 0;
}
