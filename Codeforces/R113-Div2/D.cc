#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int>::const_iterator vci;
typedef map<int, int>::const_iterator mci;

const int MAXN = 100010;

int n, m;
vector<pii> shoes;
map<int, int> id;

vector<int> edge[MAXN];

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

pair<long long, int> hungarian(int n)
{
    long long sum = 0;
    int cnt = 0;
    memset(match, 0xff, sizeof(match));
    for (int i = n - 1; i >= 0; i--) {
        memset(vis, 0, sizeof(vis));
        if (find_path(id[shoes[i].second])) {
            sum += shoes[i].first;
            cnt++;
        }
    }

    return pair<long long, int>(sum, cnt);
}

int main()
{
    while (cin >> n) {
        shoes.clear();

        for (int i = 0; i < n; i++) {
            int c, s;
            cin >> c >> s;
            shoes.push_back(pii(c, s));
            id[s] = i + 1;

            edge[i + 1].clear();
        }

        cin >> m;
        for (int i = 1; i <= m; i++) {
            int d, l;
            cin >> d >> l;

            mci it = id.find(l);
            if (it != id.end() && shoes[it->second - 1].first <= d) {
                edge[it->second].push_back(i);
            }
            it = id.find(l + 1);
            if (it != id.end() && shoes[it->second - 1].first <= d) {
                edge[it->second].push_back(i);
            }
        }

        sort(shoes.begin(), shoes.end());

        pair<long long, int> ans = hungarian(n);

        cout << ans.first << endl;
        cout << ans.second << endl;
        for (int i = 1; i <= m; i++) {
            if (match[i] != -1) {
                cout << i << " " << match[i] << endl;
            }
        }
    }

    return 0;
}

