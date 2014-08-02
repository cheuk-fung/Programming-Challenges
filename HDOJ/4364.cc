/*
 *  SRC: HDOJ 4364
 * PROB: Matrix operation
 * ALGO: NULL
 * DATE: Aug 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

const int M[4][4] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}
};
int A[4][4], R[4][4];

inline int multiply(int x, int y)
{
    if (y == 1) return x;

    int r = x << 1;
    if (r > 0xFF) r ^= 0x1B;
    if (y == 2) return r;
    return r ^ x;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                scanf("%x", &A[i][j]);
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                R[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    R[i][j] ^= multiply(A[k][j], M[i][k]);
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%02X%c", R[i][j] & 0xFF, j + 1 == 4 ? '\n' : ' ');
            }
        }

        if (tasks) putchar(10);
    }

    return 0;
}

