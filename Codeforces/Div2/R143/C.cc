#include <iostream>
#include <algorithm>

using namespace std;

long long a[100010];
long long s[100010];

int main()
{
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    int cnt = 1;
    long long ans = a[1];
    for (int i = 2; i <= n; i++) {
        int l = 1, r = i - 1;
        while (l < r) {
            int mid = (l + r - 1) >> 1;
            long long sum = a[i] * (i - mid + 1) - (s[i] - s[mid - 1]);
            if (sum <= k) r = mid;
            else l = mid + 1;
        }
        long long sum = a[i] * (i - l + 1) - (s[i] - s[l - 1]);
        if (sum <= k && i - l + 1 > cnt) {
            cnt = i - l + 1;
            ans = a[i];
        }
    }

    cout << cnt << " " << ans << endl;

    return 0;
}

