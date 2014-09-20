#include <cstring>
#include <iostream>

using namespace std;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

int n, u, r;
long long ans;
int a[50], b[50], p[50];
long long k[50];

long long calc()
{
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i] * k[i];
    }
    return res;
}

void dfs(int x, int pre)
{
    if (!x) {
        ans = max(ans, calc());
        return ;
    }

    if (!(x & 1)) ans = max(ans, calc());
    else {
        for (int i = 0; i < n; i++) a[i] ^= b[i];
        ans = max(ans, calc());
        for (int i = 0; i < n; i++) a[i] ^= b[i];
    }

    int newa[n], olda[n];
    for (int i = 0; i < n; i++) newa[i] = a[p[i]] + r;
    memmove(olda, a, sizeof(int) * n);
    memmove(a, newa, sizeof(int) * n);
    dfs(x - 1, 1);
    memmove(a, olda, sizeof(int) * n);

    if (pre) {
        for (int i = 0; i < n; i++) a[i] ^= b[i];
        dfs(x - 1, 0);
        for (int i = 0; i < n; i++) a[i] ^= b[i];
    }
}

int main()
{
    while (cin >> n >> u >> r) {
        ans = -LLINF;
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) cin >> k[i];
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) p[i]--;

        dfs(u, 1);
        cout << ans << endl;
    }

    return 0;
}

