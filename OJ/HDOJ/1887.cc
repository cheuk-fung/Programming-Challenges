/*
 *  SRC: HDOJ 1887
 * PROB: Weird Numbers
 * ALGO: NULL
 * DATE: Aug 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>

int mypow[11][30];

int main()
{
    for (int i = 2; i <= 10; i++) {
        mypow[i][0] = 1;
        for (int j = 1; mypow[i][j - 1] <= 10000000; j++)
            mypow[i][j] = mypow[i][j - 1] * -i;
    }

    char cmd[10];
    while (scanf("%s", cmd), cmd[0] != 'e') {
        if (cmd[0] == 't') {
            int r = 0;
            char* p = cmd + 3;
            while (*p) r = r * 10 + *p++ - '0';
            r *= -1;

            int n;
            scanf("%d", &n);
            if (n == 0) {
                puts("0");
                continue;
            }

            char ans[30];
            int cnt = 0;
            while (n) {
                int x = n / r;
                ans[cnt] = n - x * r;
                if (ans[cnt] < 0) {
                    ans[cnt] -= r;
                    x++;
                }
                ans[cnt++] += '0';
                n = x;
            }

            for (int i = cnt - 1; i >= 0; i--) putchar(ans[i]);
            putchar(10);
        }
        else {
            int r = 0;
            char* p = cmd + 5;
            while (*p) r = r * 10 + *p++ - '0';

            char str[30];
            scanf("%s", str);
            int len = strlen(str);

            int n = 0;
            for (int i = 0, j = len - 1; i < len; i++, j--)
                n += (str[i] - '0') * mypow[r][j];
            printf("%d\n", n);
        }
    }

    return 0;
}
