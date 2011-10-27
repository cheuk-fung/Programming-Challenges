/*
 *  SRC: NKOJ 1901
 * PROB: Candies Distribution
 * ALGO: DP
 * DATE: Aug 30, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::max;

int jobs, n, a[50], f[1251];

int main()
{
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%d", &n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            a[i] = abs(a[i]);
            sum += a[i];
        }
        for (int i = 0; i < n; i++)
            for (int j = sum / 2; j >= a[i]; j--)
                f[j] = max(f[j], f[j - a[i]] + a[i]);
        printf("%d\n", abs(sum - f[sum / 2] * 2));

        memset(f, 0, sizeof(f));
    }

    return 0;
}
