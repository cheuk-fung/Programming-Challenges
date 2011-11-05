/*
 *  SRC: HDOJ 3683
 * PROB: Gomoku
 * ALGO: Gaming
 * DATE: Nov 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int dir[8][2] = {
    { 0, -1},
    {-1, -1},
    {-1,  0},
    {-1,  1},
    { 0,  1},
    { 1,  1},
    { 1,  0},
    { 1, -1}
};

char map[20][20];
int  first_win_x, first_win_y;

inline bool check(int x, int y, char c)
{
    if (!(0 <= x && x <= 14)) return false;
    if (!(0 <= y && y <= 14)) return false;
    return map[x][y] == c;
}

inline bool check_win(int x, int y, char c)
{
    for (int k = 0; k < 4; k++) {
        int a = 1, b = 1;
        while (check(x + a * dir[k][0], y + a * dir[k][1], c)) a++;
        while (check(x + b * dir[k + 4][0], y + b * dir[k + 4][1], c)) b++;
        a--;
        b--;
        if (a + b >= 4) return true;
    }
    return false;
}

int cnt_win_point(char c)
{
    int cnt = 0;
    for (int i = 0; i <= 14; i++)
        for (int j = 0; j <= 14; j++)
            if (map[i][j] == '0')
                if (check_win(i, j, c)) {
                    cnt++;
                    if (cnt == 1) {
                        first_win_x = i;
                        first_win_y = j;
                    }
                }
    return cnt;
}

void judge(char a, char b)
{
    int win_point_cnt = cnt_win_point(a);
    if (win_point_cnt) {
        printf("Place %s at (%d,%d) to win in 1 move.\n",
                a == 'b' ? "black" : "white", first_win_x, first_win_y);
        return ;
    }

    win_point_cnt = cnt_win_point(b);
    if (win_point_cnt > 1) {
        puts("Lose in 2 moves.");
        return ;
    }

    if (win_point_cnt == 1) {
        int temp_x = first_win_x,
            temp_y = first_win_y;
        map[first_win_x][first_win_y] = a;
        if (cnt_win_point(a) > 1)
            printf("Place %s at (%d,%d) to win in 3 moves.\n",
                    a == 'b' ? "black" : "white", temp_x, temp_y);
        else puts("Cannot win in 3 moves.");
        return ;
    }

    for (int i = 0; i <= 14; i++)
        for (int j = 0; j <= 14; j++)
            if (map[i][j] == '0') {
                map[i][j] = a;
                if (cnt_win_point(a) > 1) {
                    printf("Place %s at (%d,%d) to win in 3 moves.\n",
                            a == 'b' ? "black" : "white", i, j);
                    return ;
                }
                map[i][j] = '0';
            }

    puts("Cannot win in 3 moves.");
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        memset(map, '0', sizeof(map));
        int w_cnt = 0, b_cnt = 0;

        for (int i = 0; i < n; i++) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            if (c) {
                map[x][y] = 'b';
                b_cnt++;
            }
            else {
                map[x][y] = 'w';
                w_cnt++;
            }
        }
        if (!(b_cnt == w_cnt || b_cnt == w_cnt + 1)) {
            puts("Invalid.");
            continue;
        }

        if (b_cnt == w_cnt) judge('b', 'w');
        else judge('w', 'b');
    }

    return 0;
}
