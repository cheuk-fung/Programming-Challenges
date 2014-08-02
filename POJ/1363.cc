/*
 *  SRC: POJ 1363
 * PROB: Rails
 * ALGO: NULL
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n, a[1000];

void solve()
{
    for (int i = 0; i < n; i++) {
        int pre = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                if (pre == 0) {
                    pre = a[j];
                    continue;
                }
                if (a[j] < pre) {
                    pre = a[j];
                    continue;
                }
                puts("No");
                return ;
            }
        }
    }

    puts("Yes");
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;

        scanf("%d", a);
        while (a[0] != 0) {
            for (int i = 1; i < n; i++)
                scanf("%d", a + i);
            solve();

            scanf("%d", a);
        }
        putchar(10);
    }

    return 0;
}
