/*
 *  SRC: HDOJ 3935
 * PROB: Dark Room
 * ALGO: Bitwise Operation
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int board[110];
int new_board[110];
int final;

inline int count_one(int x)
{
    x = (x & 0x55555555) + ((x >>  1) & 0x55555555);
    x = (x & 0x33333333) + ((x >>  2) & 0x33333333);
    x = (x & 0x0f0f0f0f) + ((x >>  4) & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + ((x >>  8) & 0x00ff00ff);
    x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
    return x;
}

int count_board(int n, int m)
{
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int opr = (~new_board[i - 1]) & final;
        new_board[i] ^= opr ^ (opr >> 1) ^ (opr << 1);
        new_board[i] &= final;
        new_board[i + 1] ^= opr;
        cnt += count_one(opr);
    }

    if (new_board[n] != final) {
        return INF;
    }

    return cnt;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        final = (1 << m) - 1;
        for (int i = 1; i <= n; i++) {
            board[i] = 0;
            for (int j = 0; j < m; j++) {
                int b;
                scanf("%d", &b);
                board[i] = (board[i] << 1) + b;
            }
        }

        int ans = INF;
        for (int i = final; i >= 0; i--) {
            memcpy(new_board, board, sizeof(board));
            new_board[0] = i;
            ans = min(ans, count_board(n, m));
        }

        if (ans == INF) {
            puts("no solution");
        } else {
            printf("%d\n", ans);
        }
    }

    return 0;
}

