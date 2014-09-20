#include <iostream>

using namespace std;

const int MOD = 1000000007;

int cnt[] = {
    1,
    2,
    9,
    64,
    625,
    7776,
    117649,
    2097152
};

int main()
{
    int n, k;
    cin >> n >> k;

    long long ans = cnt[k - 1];
    for (int i = k; i < n; i++) {
        ans = ans * (n - k) % MOD;
    }
    cout << ans << endl;

    return 0;
}
