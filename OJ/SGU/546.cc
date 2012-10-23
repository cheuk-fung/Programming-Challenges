#include <cstdio>
#include <cstring>

const int INF = 0x3f3f3f3f;

int f[222][222][222];
int pre[222][222][222];

inline void chkmin(int a, int b, int c, int v, int p)
{
    if (v < f[a][b][c]) {
        f[a][b][c] = v;
        pre[a][b][c] = p;
    }
}

char pwd[222];

int main(int argc, char *argv[])
{
    int n, a, b;
    while (~scanf("%d%d%d", &n, &a, &b)) {
        scanf("%s", pwd);

        memset(f, 0x3f, sizeof f);
        f[0][0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= a; k++) {
                    if (f[i][j][k] == INF) continue;
                    if (pwd[i] == '0') {
                        chkmin(i + 1, j, k + 1, f[i][j][k], 0);
                        chkmin(i + 1, j + 1, k, f[i][j][k] + 1, 1);
                        chkmin(i + 1, j, k, f[i][j][k] + 1, 2);
                    } else if (pwd[i] == '1') {
                        chkmin(i + 1, j, k + 1, f[i][j][k] + 1, 0);
                        chkmin(i + 1, j + 1, k, f[i][j][k], 1);
                        chkmin(i + 1, j, k, f[i][j][k] + 1, 2);
                    } else {
                        chkmin(i + 1, j, k + 1, f[i][j][k] + 1, 0);
                        chkmin(i + 1, j + 1, k, f[i][j][k] + 1, 1);
                        chkmin(i + 1, j, k, f[i][j][k], 2);
                    }
                }
            }
        }

        if (f[n][b][a] == INF) {
            puts("-1");
        } else if (f[n][b][a] == 0) {
            printf("0\n%s\n", pwd);
        } else {
            printf("%d\n", f[n][b][a]);
            for (int i = n; i >= 1; i--) {
                pwd[i - 1] = pre[i][b][a] + '0';
                if (pre[i][b][a] == 0) a--;
                else if (pre[i][b][a] == 1) b--;
            }
            puts(pwd);
        }
    }

    return 0;
}
