#include <iostream>

using namespace std;

int main()
{
    int n, cnt[5] = {0};
    cin >> n;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        cnt[s]++;
    }

    int ans = cnt[4] + cnt[3] + cnt[2] / 2;
    cnt[1] -= cnt[3];
    if (cnt[2] % 2) {
        ans++;
        cnt[1] -= 2;
    }
    if (cnt[1] > 0) {
        ans += cnt[1] / 4;
        if (cnt[1] % 4) ans++;
    }
    cout << ans << endl;

    return 0;
}

