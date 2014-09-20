#include <cstdio>
#include <iostream>

using namespace std;

const int MOD = 1000000007;

int main()
{
    int n, m, k;
    long long res;
    cin >> n >> m >> k;
    if (k > n || k <= 1) {
        res = 1;
        for (int i = 0; i < n; i++) res = (res * m) % MOD;
    }
    else if (k == n) {
        res = 1;
        for (int i = 0; i < (n + 1) / 2; i++) res = (res * m) % MOD;
    }
    else if (k % 2) res = (m * m) % MOD;
    else res = m;

    cout << res << endl;

    return 0;
}

