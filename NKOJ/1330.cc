/*
 *  SRC: NKOJ p1330
 * PROB: Square Ice
 * ALGO: string
 * DATE: Jul 27, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

char map[100][100];

int main()
{
    int m, CASE = 1;
    while (scanf("%d", &m), m != 0) {
        if (CASE > 1) puts("");
        memset(map, ' ', sizeof(map));
        int len;
        for (int i = 1; i <= m; i++) {
            len = 1;
            for (int j = 1; j <= m; j++) {
                int c;
                scanf("%d", &c);
                switch(c) {
                    case 0:
                        int delta;
                        if (j == 1 || map[i * 4][len - 2] == 'O') {
                            map[i * 4][len] = 'H';
                            map[i * 4][len + 1] = '-';
                            map[i * 4][len + 2] = 'O';
                            delta = 2;
                        }
                        else {
                            map[i * 4][len] = 'O';
                            map[i * 4][len + 1] = '-';
                            map[i * 4][len + 2] = 'H';
                            delta = 0;

                        }
                        if (i == 1 || map[i * 4 - 2][len + delta] == 'H') {
                            map[i * 4 + 1][len + delta] = '|';
                            map[i * 4 + 2][len + delta] = 'H';
                        }
                        else {
                            map[i * 4 - 1][len + delta] = '|';
                            map[i * 4 - 2][len + delta] = 'H';

                        }
                        len += 3;
                        map[i * 4][len++] = ' ';
                        break;
                    case 1:
                        map[i * 4][len++] = 'H';
                        map[i * 4][len++] = '-';
                        map[i * 4][len++] = 'O';
                        map[i * 4][len++] = '-';
                        map[i * 4][len++] = 'H';
                        map[i * 4][len++] = ' ';
                        break;
                    case -1:
                        map[i * 4 - 2][len] = 'H';
                        map[i * 4 - 1][len] = '|';
                        map[i * 4][len] = 'O';
                        map[i * 4 + 1][len] = '|';
                        map[i * 4 + 2][len++] = 'H';
                        map[i * 4][len++] = ' ';
                }
            }
        }

        printf("Case %d:\n\n", CASE++);
        for (int i = 0; i < len; i++) putchar('*');
        puts("");
        for (int i = 0; i <= 4 * (m + 1); i++)
            for (int j = 0; j < len; j++)
                if (map[i][j] != ' ') {
                    map[i][0] = '*';
                    map[i][len - 1] = '*';
                    map[i][len] = '\0';
                    puts(map[i]);
                    break;
                }
        for (int i = 0; i < len; i++) putchar('*');
        puts("");
    }

    return 0;
}

