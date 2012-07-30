#include <cstdio>
#include <cstring>

int mat[101][101];
int f[101][101];
int vase[101][101];

void print_vase(int x, int y)
{
    if (x != 1) {
        print_vase(x - 1, vase[x][y] - 1);
        putchar(' ');
    }
    printf("%d", vase[x][y]);
}

int main(int argc, char *argv[])
{
    int n, v;
    scanf("%d%d", &n, &v);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= v; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    memset(f, 0xaf, sizeof f);
    for (int i = 0; i <= v; i++) f[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= v; j++) {
            f[i][j] = f[i - 1][j - 1] + mat[i][j];
            vase[i][j] = j;
            if (f[i][j - 1] > f[i][j]) {
                f[i][j] = f[i][j - 1];
                vase[i][j] = vase[i][j - 1];
            }
        }
    }

    printf("%d\n", f[n][v]);
    print_vase(n, v);
    putchar(10);

    return 0;
}
