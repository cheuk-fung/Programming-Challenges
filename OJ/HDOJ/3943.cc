/*
 *  SRC: HDOJ 3943
 * PROB: K-th Nya Number
 * ALGO: DP
 * DATE: Oct 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

char s[30];
int len;
unsigned long long f[21][21][21];

unsigned long long dp(int pos, int x, int y, bool limit)
{
    if (pos == len) return x == 0 && y == 0;
    if (x < 0 || y < 0) return 0;

    int rest = len - pos - 1;
    if (!limit && f[rest][x][y] != ~0ull) return f[rest][x][y];
    int upper = limit ? s[pos] - '0' : 10;
    unsigned long long res = 0;
    for (int i = 0; i < upper; i++) {
        res += dp(pos + 1, x - (i == 4), y - (i == 7), false);
    }
    if (limit) res += dp(pos + 1, x - (upper == 4), y - (upper == 7), true);
    else f[rest][x][y] = res;

    return res;
}

unsigned long long check(unsigned long long n, int x, int y)
{
    sprintf(s, "%I64u", n);
    len = strlen(s);

    return dp(0, x, y, true);
}

int main()
{
    memset(f, 0xff, sizeof f);

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case #%d:\n", task);

        unsigned long long p, q;
        int x, y;
        scanf("%I64u%I64u%d%d", &p, &q, &x, &y);
        unsigned long long lres = check(p, x, y);
        unsigned long long rres = check(q, x, y);
        unsigned long long tot = rres - lres;

        int n;
        scanf("%d", &n);
        while (n--) {
            unsigned long long k;
            scanf("%I64u", &k);
            if (k <= tot) {
                unsigned long long l = p, r = q;
                while (l < r) {
                    unsigned long long mid = (l + r - 1) >> 1;
                    if (check(mid, x, y) - lres >= k) r = mid;
                    else l = mid + 1;
                }
                printf("%I64u\n", l);
            } else {
                puts("Nya!");
            }
        }
    }

    return 0;
}
