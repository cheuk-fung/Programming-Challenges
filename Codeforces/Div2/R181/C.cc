#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000010;

int psum, p[MAXN];
bool b[MAXN];

void prime()
{
    memset(b, true, sizeof(b));
    b[0] = b[1] = false;

    for (int i = 0; i < MAXN; i++) {
        if (b[i]) p[psum++] = i;
        for (int j = 0; j < psum && i * p[j] < MAXN; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }
}

int C(int n, int k)
{
    long long res = 1;
    for (int i = 0; i < psum && n >= p[i]; i++) {
        int a = n, b = k, c = n - k;
        int cnt = 0;

        while (a > 1) {
            a /= p[i];
            cnt += a;
        }

        while (b > 1) {
            b /= p[i];
            cnt -= b;
        }

        while (c > 1) {
            c /= p[i];
            cnt -= c;
        }

        long long now = 1;
        for (long long px = p[i]; cnt; cnt >>= 1) {
            if (cnt & 1) now = now * px % MOD;
            px = px * px % MOD;
        }
        res = res * now % MOD;
    }
    return res;
}

bool check(int a, int b, int n)
{
    while (n) {
        if (n % 10 != a && n % 10 != b) {
            return false;
        }
        n /= 10;
    }
    return true;
}

int main()
{
    prime();

    int a, b, n;
    while (cin >> a >> b >> n) {
        long long count = 0;
        for (int i = 0; i <= n; i++) {
            int now = a * i + b * (n - i);
            if (check(a, b, now)) {
                count = (count + C(n, i)) % MOD;
            }
        }
        cout << count << endl;
    }

    return 0;
}
