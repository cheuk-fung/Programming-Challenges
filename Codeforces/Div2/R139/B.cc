#include <iostream>

using namespace std;

int cnt;
long long f[100];
long long ans[100];

bool dfs(int s, int now, int x)
{
    if (s == 0) {
        if (x < 2) {
            ans[x++] = 0;
        }
        cout << x << endl;
        for (int i = 0; i < x; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        return true;
    }
    for (int i = now; i >= 2; i--) {
        if (s < f[i]) continue;
        ans[x] = f[i];
        bool r = dfs(s - f[i], i - 1, x + 1);
        if (r) return true;
    }
    return false;
}

int main()
{
    int s, k;
    while (cin >> s >> k) {
        f[0] = 0;
        f[1] = 1;
        int cnt = 2;
        while (f[cnt - 1] <= s) {
            f[cnt] = 0;
            for (int j = 0; cnt - j - 1 >= 0 && j < k; j++) {
                f[cnt] += f[cnt - j - 1];
            }
            cnt++;
        }
        dfs(s, cnt - 1, 0);
    }

    return 0;
}

