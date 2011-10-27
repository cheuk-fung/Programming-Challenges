/*
ID: os.idea1
LANG: C
TASK: ttwo
*/
#include <stdio.h>

struct set
{
    int a, b, d;
} f, c;

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    FILE *fin=fopen("ttwo.in","r");
    FILE *fout=fopen("ttwo.out","w");

    char map[10][10];
    long i, j;

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
        {
            fscanf(fin, "%c", &map[i][j]);
            if (map[i][j] == '\n') fscanf(fin, "%c", &map[i][j]);
            if (map[i][j] == 'F')
            {
                f.a = i; f.b = j; f.d = 0;
            }
            if (map[i][j] == 'C')
            {
                c.a = i; c.b = j; c.d = 0;
            }
        }

    for (i = 1; i < 40001; i++)
    {
        if (0 <= f.a + dir[f.d][0] && f.a + dir[f.d][0] < 10 && 0 <= f.b + dir[f.d][1] && f.b + dir[f.d][1] < 10)
        {
            if (map[f.a + dir[f.d][0]][f.b + dir[f.d][1]] != '*')
            {
                map[f.a][f.b] = '.';
                f.a += dir[f.d][0];
                f.b += dir[f.d][1];
                map[f.a][f.b] = 'F';
            }
            else f.d = (++f.d) % 4;
        }
        else f.d = (++f.d) % 4;

        if (0 <= c.a + dir[c.d][0] && c.a + dir[c.d][0] < 10 && 0 <= c.b + dir[c.d][1] && c.b + dir[c.d][1] < 10)
        {
            if (map[c.a + dir[c.d][0]][c.b + dir[c.d][1]] != '*')
            {
                map[c.a][c.b] = '.';
                c.a += dir[c.d][0];
                c.b += dir[c.d][1];
                map[c.a][c.b] = 'C';
            }
            else c.d = (++c.d) % 4;
        }
        else c.d = (++c.d) % 4;

        if (f.a == c.a && f.b == c.b) break;
    }

    if (i == 40001) fprintf(fout, "0\n");
    else fprintf(fout, "%ld\n", i);

    fclose(fin); fclose(fout);

    return 0;
}

