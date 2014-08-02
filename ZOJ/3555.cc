/*
 *  SRC: ZOJ 3555
 * PROB: Ice Climber
 * ALGO: Implementation
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

char mat[5000][110];
long long f[2][110];
int n, m, tmv, tjmp, tbat;
int curr, next;

int main()
{
    while (~scanf("%d%d%d%d%d", &n, &m, &tmv, &tjmp, &tbat)) {
        tbat += tmv;

        for (int i = 0; i < 2 * n; i++) {
            scanf("%s", mat[i]);
        }

        memset(f, 0x3f, sizeof f);
        curr = 0, next = 1;
        f[curr][0] = 0;
        for (int i = 1; i < m; i++) {
            if (mat[2 * n - 1][i] == '0') break;
            bool ok = true;
            switch (mat[2 * n - 2][i]) {
                case '0': f[curr][i] = f[curr][i - 1] + tmv; break;
                case '#': f[curr][i] = f[curr][i - 1] + tbat; break;
                case '|': ok = false; break;
            }
            if (!ok) break;
        }

        for (int i = 2 * n - 2; i > 0; i -= 2) {
            for (int j = 0; j < m; j++) {
                if (f[curr][j] == LLINF) continue;
                if (mat[i + 1][j] == '0') continue;
                if (mat[i - 2][j] == '|') continue;
                long long now = f[curr][j] + (mat[i - 1][j] - '0' + 1) * tjmp;
                bool ok = true;
                if (j && (mat[i - 2][j - 1] != '0' || mat[i - 1][j - 1] == '0')) ok = false;
                if (j && ok) f[next][j - 1] = min(f[next][j - 1], now);
                for (int k = j - 2; k >= 0; k--) {
                    if (!ok) break;
                    if (mat[i - 1][k] == '0') break;
                    switch (mat[i - 2][k]) {
                        case '0': now += tmv; f[next][k] = min(f[next][k], now); break;
                        case '#': now += tbat; f[next][k] = min(f[next][k], now); break;
                        case '|': ok = false; break;
                    }
                }

                now = f[curr][j] + (mat[i - 1][j] - '0' + 1) * tjmp;
                ok = true;
                if (j + 1 < m && (mat[i - 2][j + 1] != '0' || mat[i - 1][j + 1] == '0')) ok = false;
                if (j + 1 < m && ok) f[next][j + 1] = min(f[next][j + 1], now);
                for (int k = j + 2; k < m; k++) {
                    if (!ok) break;
                    if (mat[i - 1][k] == '0') break;
                    switch (mat[i - 2][k]) {
                        case '0': now += tmv; f[next][k] = min(f[next][k], now); break;
                        case '#': now += tbat; f[next][k] = min(f[next][k], now); break;
                        case '|': ok = false; break;
                    }
                }
            }

            curr ^= 1;
            next ^= 1;
            memset(f[next], 0x3f, sizeof f[next]);
        }

        long long ans = LLINF;
        for (int i = 0; i < m; i++) {
            ans = min(ans, f[curr][i]);
        }
        printf("%lld\n", ans == LLINF ? -1 : ans);
    }

    return 0;
}

