#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

class Disjoint_Set {
    public:
        // a[i] > 0: a[i] is i's ancestor;
        // a[i] < 0: -a[i] is the number of elements sharing the same ancestor i
        int a[50];

        void build() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) {
                a[x] += a[y];
                a[y] = x;
            }
        }
} ds;

int main()
{
    int n, m;
    cin >> n >> m;
    ds.build();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        ds.join(a, b);
    }

    vector<int> team[n + 1];
    for (int i = 1; i <= n; i++) {
        int r = ds.find(i);
        if (ds.a[r] < -3) {
            cout << -1 << endl;
            return 0;
        }
        team[r].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (team[i].size() == 2) {
            for (int j = 1; j <= n; j++) {
                if (j != i && team[j].size() == 1) {
                    team[i].push_back(j);
                    team[j].clear();
                    break;
                }
            }
        }
        if (team[i].size() == 2) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (team[i].size() == 0) continue;
        while (team[i].size() != 3) {
            for (int j = 1; j <= n; j++) {
                if (j != i && team[j].size() == 1) {
                    team[i].push_back(j);
                    team[j].clear();
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (team[i].size() == 0) continue;
        assert(team[i].size() == 3);
        for (int j = 0; j < 3; j++) {
            cout << team[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
