#include <iostream>

using namespace std;

int deg[1000010];

int main()
{
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        deg[b]++;
    }

    long long tot = (long long)n * (n - 1) * (n - 2) / 6;
    long long bad = 0;
    for (int i = 1; i <= n; i++) {
        bad += deg[i] * (n - 1ll - deg[i]);
    }
    cout << tot - bad / 2 << endl;

    return 0;
}
