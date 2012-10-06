/*
 *  SRC: HDOJ 2089
 * PROB: 不要62
 * ALGO: DP
 * DATE: Oct 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

int f[10][3];
/*
 * f[][0]: does not contain 4 or 62
 * f[][1]: does not contain 4 or 62 and begin with 2
 * f[][2]: contains 4 or 62
 */

int calc(int n)
{
    char s[20];
    sprintf(s, "%d", n);

    int res = 0;
    bool bad = false;
    for (int i = 0, len = strlen(s); i < len; i++) {
        res += f[len - i - 1][2] * (s[i] - '0');
        if (bad) {
            res += f[len - i - 1][0] * (s[i] - '0');
        } else {
            if (s[i] > '4') res += f[len - i - 1][0];
            if (s[i] > '6') res += f[len - i - 1][1];
            if (i > 0 && s[i - 1] == '6' && s[i] > '2') res += f[len - i][1];
            if (s[i] == '4' || (i > 0 && s[i - 1] == '6' && s[i] == '2')) bad = true;
        }
    }
    return n - res;
}

int main()
{
    f[0][0] = 1;
    for (int i = 1; i < 10; i++) {
        f[i][0] = f[i - 1][0] * 9 - f[i - 1][1];
        f[i][1] = f[i - 1][0];
        f[i][2] = f[i - 1][2] * 10 + f[i - 1][0] + f[i - 1][1];
    }

    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        int lres = calc(n);
        int rres = calc(m + 1);
        printf("%d\n", rres - lres);
    }

    return 0;
}

