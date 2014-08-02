/*
 *  SRC: HDOJ 4246
 * PROB: A Famous Airport Manager
 * ALGO: DFS
 * DATE: Jul 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int task;
int res[256];
int conn[8][1 << 8];
int f[1 << 16];

bool floodfill(int *mat, int x)
{
    if (x == 0) return true;
    if (*mat & (1 << x)) return false;

    *mat |= 1 << x;

    return
        (x > 2 && floodfill(mat, x - 3)) ||
        (x < 6 && floodfill(mat, x + 3)) ||
        (x % 3 && floodfill(mat, x - 1)) ||
        ((x + 1) % 3 && floodfill(mat, x + 1));
}

bool connect(int status, int x)
{
    int mask = 0;
    for (int i = 0; i < 16; i += 2) {
        if (status & (2 << i)) {
            mask |= 1 << (i >> 1);
        }
    }
    if (conn[x][mask] > -1) return conn[x][mask];
    int mat = (mask & ~(1 << x)) << 1;
    return (conn[x][mask] = floodfill(&mat, x + 1));
}

void search(int status, int order)
{
    if (status == 0) {
        res[order] = task;
        return ;
    }

    for (int i = 0; i < 16; i += 2) {
        if ((status & (2 << i)) && connect(status, i >> 1)) {
            search(status & ~(3 << i), (order << 1) | ((status >> i) & 1));
        }
    }
}

int main()
{
    memset(conn, 0xff, sizeof(conn));
    memset(f, 0xff, sizeof(f));

    task = 1;
    char mat[3][4];
    while (~scanf("%s %s %s", mat[0], mat[1], mat[2])) {
        int status = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = (i * 3 + j) << 1;
                if (mat[i][j] == 'G') {
                    status |= 2 << x;
                } else if (mat[i][j] == 'B') {
                    status |= 3 << x;
                }
            }
        }

        if (f[status >> 2] == -1) {
            int cnt = 0;
            search(status >> 2, 0);

            for (int i = 0; i < 256; i++) {
                if (res[i] == task) {
                    cnt++;
                }
            }
            f[status >> 2] = cnt;
        }
        printf("Case %d: %d\n", task++, f[status >> 2]);
    }

    return 0;
}

