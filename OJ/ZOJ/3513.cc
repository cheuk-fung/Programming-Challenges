/*
 *  SRC: ZOJ 3513
 * PROB: Human or Pig
 * ALGO: NULL
 * DATE: Oct 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>

int x, y;
int f[50010][2]; // 0: P, 1: H

inline int ID(int i, int j) { return i * y + j; }

bool judge(int i, int j, int s)
{
    if (s) {
        for (int k = 1; i - k * j > 0; k++) {
            if (f[ID(i - k * j, j)][0]) {
                return true;
            }
        }
        for (int k = 1; j - k * i > 0; k++) {
            if (f[ID(i, j - k * i)][0]) {
                return true;
            }
        }
        return false;
    }

    for (int k = 1; i - k * j >= 0; k++) {
        if (!f[ID(i - k * j, j)][1]) {
            return false;
        }
    }
    for (int k = 1; j - k * i >= 0; k++) {
        if (!f[ID(i, j - k * i)][1]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int task = 1;
    while (~scanf("%d%d", &x, &y)) {
        printf("Case #%d:\n", task++);
        for (int j = 0; j <= y; j++) {
            f[ID(0, j)][0] = 0;
            f[ID(0, j)][1] = 1;
        }
        for (int i = 0; i <= x; i++) {
            f[ID(i, 0)][0] = 0;
            f[ID(i, 0)][1] = 1;
        }
        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= y; j++) {
                f[ID(i, j)][1] = judge(i, j, 1);
                f[ID(i, j)][0] = !f[ID(i, j)][1];
                if (f[ID(i, j)][1]) {
                    putchar('H');
                } else {
                    // assert(judge(i, j, 0));
                    putchar('P');
                }
            }
            putchar(10);
        }
    }

    return 0;
}

