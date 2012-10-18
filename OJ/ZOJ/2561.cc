/*
 *  SRC: ZOJ 2561
 * PROB: Order-Preserving Codes
 * ALGO: DP
 * DATE: Oct 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 2012;

long long occurence[MAXN];
long long f[MAXN][MAXN];
int s[MAXN][MAXN];

char code[MAXN << 7];

void generate(int l, int r, int length)
{
    if (l == r) {
        code[length] = '\0';
        puts(code);
        return ;
    }

    code[length] = '0';
    generate(l, s[l][r], length + 1);

    code[length] = '1';
    generate(s[l][r] + 1, r, length + 1);
}

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) scanf("%lld", occurence + i);
        for (int i = 1; i <= n; i++) occurence[i] += occurence[i - 1];

        memset(f, 0x3f, sizeof f);
        for (int i = 0; i <= n; i++) {
            f[i][i] = 0;
            s[i][i] = i;
        }
        for (int l = 1; l <= n; l++) {
            for (int i = 1; i + l <= n; i++) {
                int j = i + l;
                for (int k = s[i][j - 1]; k <= s[i + 1][j]; k++) {
                    long long now = f[i][k] + f[k + 1][j] + occurence[j] - occurence[i - 1];
                    if (now <= f[i][j]) {
                        f[i][j] = now;
                        s[i][j] = k;
                    }
                }
            }
        }

        // printf("%lld\n", f[1][n]);
        generate(1, n, 0);
    }

    return 0;
}

