#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1e6 + 10;

int a, b, k;
int prmcnt, prm[MAXN];
bool isprm[MAXN];

int get_prime(int n, int* p, bool* b)
{
    int cnt = 0;
    memset(b, true, sizeof(bool) * n);
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[cnt++] = i;
        for (int j = 0; j < cnt && i * p[j] < n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return cnt;
}

bool check(int l)
{
    for (int x = a; x <= b - l + 1; x++) {
        int low = lower_bound(prm, prm + prmcnt, x) - prm;
        int high = upper_bound(prm, prm + prmcnt, x + l - 1) - prm;
        if (high - low < k) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);

    prmcnt = get_prime(MAXN, prm, isprm);

    cin >> a >> b >> k;

    int low = 1, high = b - a + 1;
    while (low < high) {
        int mid = (low + high - 1) >> 1;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    if (check(low)) {
        cout << low << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}

