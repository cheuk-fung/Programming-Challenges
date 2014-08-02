/*
 *  SRC: HDOJ 4258
 * PROB: Covered Walkway
 * ALGO: DP
 * DATE: Aug 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline long long SQR(long long x) { return x * x; }

const int MAXN = 1000010;
int x[MAXN], ep[MAXN], s[MAXN];
long long f[MAXN];

int main()
{
    int n, c;
    while (scanf("%d%d", &n, &c), n || c) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", x + i);
        }
        x[0] = x[1];

        int top = 0;
        ep[top++] = 0;
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            int pos = lower_bound(ep, ep + top, i) - ep;
            if (pos == top || ep[pos] != i) pos--;
            f[i] = f[s[pos]] + SQR(x[i] - x[s[pos] + 1]) + c;
            // printf("%d %d %lld\n", i, s[pos], f[i]);
            while (f[s[top - 1]] + SQR(x[s[top - 1] + 1] - x[ep[top - 1]]) >= f[i] + SQR(x[i + 1] - x[ep[top - 1]])) top--;

            int l = ep[top - 1] + 1, r = n + 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (f[s[top - 1]] + SQR(x[s[top - 1] + 1] - x[mid]) >= f[i] + SQR(x[i + 1] - x[mid])) r = mid;
                else l = mid + 1;
            }
            if (l != n + 1) {
                ep[top] = l;
                s[top++] = i;
            }
        }

        printf("%I64d\n", f[n]);
    }

    return 0;
}

