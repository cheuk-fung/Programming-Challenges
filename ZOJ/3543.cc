/*
 *  SRC: ZOJ 3543
 * PROB: Number String
 * ALGO: DP
 * DATE: Oct 02, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MOD = 1000000007;

int f[1010][1010];
char str[1010];

int main()
{
    str[0] = str[1] = '0';
    while (scanf("%s", str + 2) != EOF) {
        int len = strlen(str);

        memset(f, 0, sizeof(f));
        f[1][1] = 1;
        for (int i = 2; i < len; i++)
            switch (str[i]) {
                case 'I': 
                    for (int j = 1; j <= i; j++)
                        f[i][j] = (f[i - 1][j - 1] + f[i][j - 1]) % MOD;
                    break;
                case 'D': 
                    for (int j = 1; j <= i; j++) {
                        f[i][j] = f[i - 1][i - 1] - f[i - 1][j - 1];
                        while (f[i][j] < 0) f[i][j] += MOD;
                        f[i][j] = (f[i][j] + f[i][j - 1]) % MOD;
                    }
                    break;
                case '?':
                    for (int j = 1; j <= i; j++)
                        f[i][j] = (f[i - 1][i - 1] + f[i][j - 1]) % MOD;
            }

        printf("%d\n", f[len - 1][len - 1]);
    }

    return 0;
}
