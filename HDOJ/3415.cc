/*
 *  SRC: HDOJ 3415
 * PROB: Max Sum of Max-K-sub-sequence
 * ALGO: Monotone Priority Queue
 * DATE: Aug 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int MAXN = 200012;

int a[MAXN], sum[MAXN];
int que[MAXN];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            a[i + n] = a[i];
        }
        sum[0] = a[0];
        for (int i = 0; i < n << 1; i++) {
            sum[i] = sum[i - 1] + a[i];
        }

        int ans = sum[0], l = 1, r = 1;
        int head = 0, tail = 0;
        for (int i = 0; i < n << 1; i++) {
            int j = i - k + 1;
            if (j < 0) j = 0;
            while (head < tail && i - que[head] >= k) head++;
            while (head < tail && sum[que[tail - 1]] < sum[i]) tail--;
            que[tail++] = i;
            int now = sum[que[head]] - (j == 0 ? 0 : sum[j - 1]);
            if (now > ans) {
                ans = now;
                l = j + 1;
                r = que[head] % n + 1;
            }
        }

        printf("%d %d %d\n", ans, l, r);
    }

    return 0;
}

