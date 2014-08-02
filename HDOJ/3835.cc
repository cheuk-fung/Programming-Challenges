/*
 *  SRC: HDOJ 3835
 * PROB: R(N)
 * ALGO: NULL
 * DATE: Apr 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int cnt = 0;

        for (int a = 0, loop_end = sqrt(n) + 1; a <= loop_end; a++) {
            int b = sqrt(n - a * a);
            if (b * b == n - a * a) {
                if (!a || !b) {
                    cnt += 2;
                } else {
                    cnt += 4;
                }
            }
        }

        printf("%d\n", cnt);
    }

    return 0;
}
