/*
 *  SRC: NKOJ p1434
 * PROB: Sudoku
 * ALGO: DFS
 * DATE: Jul 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int map[10][10];
int sum[10][10], avai[10][10][10];
int used[10];
int space;
int row[10];

const int sig[10][10] = {
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8}
};

const int pos[10][2] = {
    {0, 0},
    {0, 3},
    {0, 6},
    {3, 0},
    {3, 3},
    {3, 6},
    {6, 0},
    {6, 3},
    {6, 6},
};

void printSudoku()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            printf("%d", map[i][j]);
    }
    putchar(10);
}

int dfs();

int extend(int x, int y, int c)
{
    map[x][y] = c;
    space--;
    row[x]--;

    if (dfs()) return 1;

    map[x][y] = 0;
    space++;
    row[x]++;

    return 0;
}

int checkPoint(int x, int y)
{
    memset(used, 0, sizeof(used));

    for (int j = 0; j < 9; j++)
        used[map[x][j]] = 1;

    for (int i = 0; i < 9; i++)
        used[map[i][y]] = 1;

    int lpX = pos[sig[x][y]][0];
    int lpY = pos[sig[x][y]][1];
    for (int i = lpX; i < lpX + 3; i++)
        for (int j = lpY; j < lpY + 3; j++)
            used[map[i][j]] = 1;

    int cnt = 0;
    for (int i = 1; i <= 9; i++)
        if (!used[i]) avai[x][y][cnt++] = i;

    return cnt;
}

int checkRow()
{
    for (int i = 0; i < 9; i++) {
        if (row[i] == 0) continue;
        
        memset(used, 0, sizeof(used));

        for (int j = 0; j < 9; j++) {
            used[map[i][j]] = 1;
            for (int k = 0; k < sum[i][j]; k++)
                used[avai[i][j][k]] = 1;
        }

        for (int k = 1; k <= 9; k++)
            if (!used[k]) return 0;
    }

    return 1;
}

int dfs()
{
    if (space == 0) {
        printSudoku();
        return 1;
    }

    int min = 0x3FFFFFFF, x, y;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            if (map[i][j] == 0) {
                sum[i][j] = checkPoint(i, j);
                if (!sum[i][j]) return 0;
                if (sum[i][j] == 1)
                    return extend(i, j, avai[i][j][0]);
                if (sum[i][j] < min) {
                    min = sum[i][j];
                    x = i;
                    y = j;
                }
            }
            else sum[i][j] = 0;
        }

    if (min == 0x3FFFFFFF) return 0;

    if (!checkRow()) return 0;

    int tmp[10];
    // memcpy(tmp, avai[x][y], sizeof(avai[x][y]));
    for (int i = 0; i < min; i++)
        tmp[i] = avai[x][y][i];

     for (int i = 0; i < min; i++)
        if (extend(x, y, tmp[i])) return 1;

    return 0;
}

int main()
{
    while (1 + 1 == 2) {
        char tmp[100];
        scanf("%s", tmp);
        if (tmp[0] == 'e') break;

        space = 0;
        memset(row, 0, sizeof(row));
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (tmp[i * 9 + j] == '.') {
                    map[i][j] = 0;
                    space++;
                    row[i]++;
                }
                else map[i][j] = tmp[i * 9 + j] - '0';
            }

        dfs();
    }

    return 0;
}
