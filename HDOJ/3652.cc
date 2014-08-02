/*
 *  SRC: HDOJ 3652
 * PROB: B-number
 * ALGO: DP
 * DATE: Oct 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

unsigned int ten[11];
unsigned int f[11][13][3];
/*
 * f[][][0]: does not contain 13
 * f[][][1]: does not contain 13 and begin with 3
 * f[][][2]: contains 13
 */

int main()
{
    ten[0] = 1;
    for (int i = 1; i < 11; i++) ten[i] = ten[i - 1] * 10;
    f[0][0][0] = 1;
    for (int i = 1; i < 11; i++) {
        for (int j = 0; j < 13; j++) {
            for (int k = 0; k < 10; k++) {
                int d = (k * ten[i - 1] + j) % 13;
                if (k == 1) {
                    f[i][d][0] -= f[i - 1][j][1];
                    f[i][d][2] += f[i - 1][j][1];
                } else if (k == 3) {
                    f[i][d][1] += f[i - 1][j][0];
                }
                f[i][d][0] += f[i - 1][j][0];
                f[i][d][2] += f[i - 1][j][2];
            }
        }
    }

    int n;
    while (~scanf("%d", &n)) {
        char s[20];
        sprintf(s, "%d", n + 1);

        int cnt = 0;
        bool bad = false;
        for (int i = 0, len = strlen(s), mod = 0; i < len; i++) {
            for (int k = 0; k < s[i] - '0'; k++) {
                int d = (13 - (mod + k * ten[len - i - 1]) % 13) % 13;
                cnt += f[len - i - 1][d][2];
                if (bad) {
                    cnt += f[len - i - 1][d][0];
                } else {
                    if (k == 1) cnt += f[len - i - 1][d][1];
                    if (i && s[i - 1] == '1' && k == 3) cnt += f[len - i - 1][d][0];
                }
            }
            if (i && s[i - 1] == '1' && s[i] == '3') bad = true;
            mod = (mod + (s[i] - '0') * ten[len - i - 1]) % 13;
        }
        printf("%d\n", cnt);
    }

    return 0;
}

