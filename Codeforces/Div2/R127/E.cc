#include <iostream>

using namespace std;

const int MAXN = 100010;
long long a[MAXN];
long long lr[MAXN], lnr[MAXN];
long long rr[MAXN], rnr[MAXN];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        if (a[i - 1] > 1) {
            lr[i] = lr[i - 1] + a[i - 1];
            if (a[i - 1] & 1) lr[i]--;
        }
        if (a[i - 1] > 0) {
            lnr[i] = lnr[i - 1] + a[i - 1];
            if (!(a[i - 1] & 1)) lnr[i]--;
        }
        lnr[i] = max(lnr[i], lr[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > 1) {
            rr[i] = rr[i + 1] + a[i];
            if (a[i] & 1) rr[i]--;
        }
        if (a[i] > 0) {
            rnr[i] = rnr[i + 1] + a[i];
            if (!(a[i] & 1)) rnr[i]--;
        }
        rnr[i] = max(rnr[i], rr[i]);
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, lr[i] + rr[i]);
        ans = max(ans, lr[i] + rnr[i]);
        ans = max(ans, rr[i] + lnr[i]);
    }
    cout << ans << endl;

    return 0;
}

