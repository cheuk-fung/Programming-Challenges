#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200020;

struct Perl {
    int w, c;
} perl[MAXN];

int wsum[MAXN], csum[MAXN];

int main(int argc, char *argv[])
{
    int n, m, k;
    while (~scanf("%d%d%d", &n, &m, &k)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &perl[i].w, &perl[i].c);
            wsum[i] = wsum[i - 1] + perl[i].w;
            csum[i] = csum[i - 1] + perl[i].c;
        }

        int ans = 0;
        int acnt = 0, alow = 0;
        for (int i = 0; i + m < n; i++) {
            int wh = wsum[n - i] - wsum[n - i - m];
            int wt = wsum[n - i - m];
            if (wh > k * wt) break;

            int low = 0, high = n - i - m;
            while (low < high) {
                int mid = (low + high + 1) >> 1;
                wt = wsum[n - i - m] - wsum[mid];
                if (wh <= k * wt) low = mid;
                else high = mid - 1;
            }
            wt = wsum[n - i - m] - wsum[low];
            if (wh <= k * wt) {
                int val = csum[low] + csum[n] - csum[n - i];
                if (val > ans) {
                    ans = val;
                    acnt = i;
                    alow = low;
                }
            }
        }

        printf("%d %d\n", acnt + alow, ans);
        for (int i = 0; i < acnt; i++) putchar('H');
        for (int i = 0; i < alow; i++) putchar('T');
        putchar(10);
    }

    return 0;
}
