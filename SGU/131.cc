#include <cassert>
#include <iostream>

using namespace std;

int n, m;
long long f[11][1 << 9];

inline int chkbit(int x, int y) { return (x >> y) & 1; }
inline int setbit(int x, int y) { return x | (1 << y); }
inline int setbit(int x, int y, int z) { return x | (1 << y) | (1 << z); }

void dfs(int s, int ns, int x, int y, long long v)
{
    if (y == m) {
        assert(s + 1 == 1 << m);
        f[x + 1][ns] += v;
        return ;
    }
    if (chkbit(s, y) == 1) return dfs(s, ns, x, y + 1, v);

    if (y + 1 < m && chkbit(s, y + 1) == 0) {
        dfs(setbit(s, y, y + 1), ns, x, y + 2, v);

        if (x + 1 < n && chkbit(ns, y) == 0) {
            dfs(setbit(s, y, y + 1), setbit(ns, y), x, y + 2, v);
        }
        if (x + 1 < n && chkbit(ns, y + 1) == 0) {
            dfs(setbit(s, y, y + 1), setbit(ns, y + 1), x, y + 2, v);
        }
    }

    if (x + 1 < n && chkbit(ns, y) == 0) {
        dfs(setbit(s, y), setbit(ns, y), x, y + 1, v);

        if (y > 0 && chkbit(ns, y - 1) == 0) {
            dfs(setbit(s, y), setbit(ns, y, y - 1), x, y + 1, v);
        }
        if (y + 1 < m && chkbit(ns, y + 1) == 0) {
            dfs(setbit(s, y), setbit(ns, y, y + 1), x, y + 1, v);
        }
    }
}

int main(int argc, char *argv[])
{
    cin >> n >> m;
    dfs(0, 0, 0, 0, 1);
    for (int i = 1; i < n; i++) {
        for (int s = 0; s < 1 << m; s++) {
            dfs(s, 0, i, 0, f[i][s]);
        }
    }
    cout << f[n][0] << endl;

    return 0;
}
