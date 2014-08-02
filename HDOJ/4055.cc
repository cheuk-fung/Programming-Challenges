/*
 *  SRC: HDOJ 4055
 * PROB: Number String
 * ALGO: DP
 * DATE: Aug 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int MOD = 1000000007;

int f[1024][1024];
char s[1024];

int main()
{
    s[0] = s[1] = '0';
    while (fgets(s + 2, 1022, stdin)) {
        int len = strlen(s) - 1;
        f[1][1] = 1;
        for (int i = 2; i < len; i++) {
            switch (s[i]) {
                case 'I':
                    for (int j = 1; j <= i; j++) {
                        f[i][j] = (f[i - 1][j - 1] + f[i][j - 1]) % MOD;
                    }
                    break;
                case 'D':
                    for (int j = 1; j <= i; j++) {
                        f[i][j] = ((f[i - 1][i - 1] - f[i - 1][j - 1] + f[i][j - 1]) % MOD + MOD) % MOD;
                    }
                    break;
                case '?':
                    for (int j = 1; j <= i; j++) {
                        f[i][j] = (f[i - 1][i - 1] + f[i][j - 1]) % MOD;
                    }
            }
        }
        printf("%d\n", f[len - 1][len - 1]);
    }

    return 0;
}

