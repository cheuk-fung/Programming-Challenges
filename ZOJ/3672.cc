#include <cstdio>

const int MAXN = 10010;
int n;
long long D[MAXN], sum[MAXN];

bool check()
{
    for (int i = n - 1; i - 2 >= 0; i--) {
        long long a = sum[i - 2];
        long long b = D[i - 1];
        long long c = sum[n - 1] - a - b;
        long long x = a + c - b;
        if (0 <= x && x <= 2 * c && x % 2 == 0) return true;
    }
    if (sum[n - 1] - sum[0] == sum[0]) return true;
    return false;
}

int main()
{
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            long long A, B;
            scanf("%lld %lld", &A, &B);
            D[i] = A - B;
            sum[i] = D[i];
            if (i) sum[i] += sum[i - 1];
        }
        puts(check() ? "YES" : "NO");
    }

    return 0;
}
