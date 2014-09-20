#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
template<class T> inline int SIZE(const T &x) { return x.size(); }

int n;
int c[50], a[50][50];

pii find(int x)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c[i]; j++) {
            if (a[i][j] == x) {
                return pii(i + 1, j + 1);
            }
        }
    }
    return pii(-1, -1);
}

int main()
{
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c[i]; j++) {
            cin >> a[i][j];
        }
    }

    vector< pair<pii, pii> > s;
    for (int i = 0, now = 1; i < n; i++) {
        for (int j = 0; j < c[i]; j++, now++) {
            if (a[i][j] != now) {
                pii p = pii(i + 1, j + 1);
                pii q = find(now);
                s.push_back(make_pair(p, q));
                swap(a[i][j], a[q.first - 1][q.second - 1]);
            }
        }
    }
    cout << SIZE(s) << endl;
    for (int i = 0; i < SIZE(s); i++) cout << s[i].first.first << " " << s[i].first.second << " " << s[i].second.first << " " << s[i].second.second << endl;

    return 0;
}

