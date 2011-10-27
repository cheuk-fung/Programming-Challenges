/*
 *  SRC: HDOJ 1882
 * PROB: Strange Billboard
 * ALGO: enum
 * DATE: Aug 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

const int INF = 0x3fffffff;

int job;
int r, c, best;
int init_board[20], board[20];
char map[20][20];

inline void change(int p, int x)
{
    board[p - 1] ^= 1 << x;
    board[p] ^= 1 << x;
    board[p + 1] ^= 1 << x;
    if (x > 0) board[p] ^= 1 << (x - 1);
    if (x + 1 < c) board[p] ^= 1 << (x + 1);
}

void calc(int step)
{
    for (int i = 1; i < r; i++)
        for (int j = 0; j < c; j++)
            if (board[i - 1] & (1 << j)) {
                step++;
                if (step >= best) return ;
                change(i, j);
            }

    if (!board[r - 1]) best = step;
}

int main()
{
    while (scanf("%d%d", &r, &c), job++, r && c) {
        for (int i = 0; i < r; i++) scanf("%s", map[i]);

        if (c > r) {
            for (int i = 0; i < r; i++)
                for (int j = i + 1; j < c; j++)
                    swap(map[i][j], map[j][i]);
            swap(c, r);
        }

        for (int i = 0; i < r; i++) {
            init_board[i] = 0;
            for (int j = 0; j < c; j++) {
                init_board[i] <<= 1;
                if (map[i][j] == 'X') init_board[i]++;
            }
        }

        best = INF;
        for (int opt = 0, final = 1 << c; opt < final; opt++) {
            memcpy(board, init_board, sizeof(int) * r);

            int step = 0;
            for (int i = 0; i < c; i++) {
                if (!(opt & (1 << i))) continue;
                step++;
                change(0, i);
            }

            if (step < best) calc(step);
        }
        best  == INF ?  puts("Damaged billboard.") : printf("You have to tap %d tiles.\n", best);
    }

    return 0;
}
