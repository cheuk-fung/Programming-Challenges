/*
 *  SRC: POJ 2796
 * PROB: Feel Good
 * ALGO: NULL
 * DATE: Aug 31, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAX_N = 100001;

struct Node {
    int l, r;
} pos[MAX_N];
int n, a[MAX_N];
long long sum[MAX_N];

int main()
{
    scanf("%d", &n);
    a[0] = a[n + 1] = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        sum[i] = sum[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) {
        pos[i].l = i;
        while (a[pos[i].l - 1] >= a[i]) pos[i].l = pos[pos[i].l - 1].l;
    }

    for (int i = n; i >= 1; i--) {
        pos[i].r = i;
        while (a[pos[i].r + 1] >= a[i]) pos[i].r = pos[pos[i].r + 1].r;
    }

    long long ans = -1;
    Node best;
    for (int i = 1; i <= n; i++) {
        long long curr = (sum[pos[i].r] - sum[pos[i].l] + a[pos[i].l]) * a[i];
        if (curr > ans) {
            ans = curr;
            best = pos[i];
        }
    }
    printf("%lld\n%d %d\n", ans, best.l, best.r);

    return 0;
}
