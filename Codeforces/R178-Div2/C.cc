#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long two[1024];
long long C[2048][2048];

int main()
{
    int n, m;
    cin >> n >> m;

    two[0] = 1;
    for (int i = 1; i <= n; i++) two[i] = two[i - 1] * 2 % MOD;

    for (int i = 0; i <= n << 1; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    int light[m];
    for (int i = 0; i < m; i++) {
        cin >> light[i];
    }
    sort(light, light + m);

    int left = light[0] - 1;
    long long ans = 1;
    for (int i = 1; i < m; i++) {
        int count = light[i] - light[i - 1] - 1;
        if (count == 0) continue;
        ans = ans * two[count - 1] % MOD;
        ans = ans * C[left + count][left] % MOD;
        left += count;
    }
    ans = ans * C[left + n - light[m - 1]][left] % MOD;

    cout << ans << endl;

    return 0;
}
