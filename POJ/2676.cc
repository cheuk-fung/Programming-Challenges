/*
 *  SRC: POJ 2676
 * PROB: Sudoku
 * ALGO: DFS
 * DATE: Mar 07, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
/*
 * #include <ctime>
 * #include <cstdlib>
 */

int map[10][10];
int sum[10][10], avai[10][10][10];
int used[10];
int space;
int row[10], col[10];

const int SIG[10][10] = {
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

const int POS[10][2] = {
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
        putchar(10);
    }
    putchar(10);
}

int checkPoint(int x, int y)
{
    memset(used, 0, sizeof(used));

    for (int j = 0; j < 9; j++)
        used[map[x][j]] = 1;

    for (int i = 0; i < 9; i++)
        used[map[i][y]] = 1;

    int ltX = POS[SIG[x][y]][0];
    int ltY = POS[SIG[x][y]][1];
    for (int i = ltX; i < ltX + 3; i++)
        for (int j = ltY; j < ltY + 3; j++)
            used[map[i][j]] = 1;

    int cnt = 0;
    for (int i = 1; i <= 9; i++)
        if (!used[i]) avai[x][y][cnt++] = i;

    return cnt;
}

int checkMap()
{
    for (int i = 0; i < 9; i++) {
        if (row[i] == 0) continue;
        
        memset(used, 0, sizeof(used));

        for (int j = 0; j < 9; j++) {
            if (map[i][j]) used[map[i][j]] = 1;
            else {
                for (int k = 0; k < sum[i][j]; k++)
                    used[avai[i][j][k]] = 1;
            }
        }

        for (int k = 1; k <= 9; k++)
            if (!used[k]) return 0;
    }

    for (int j = 0; j < 9; j++) {
        if (col[j] == 0) continue;

        memset(used, 0, sizeof(used));

        for (int i = 0; i < 9; i++) {
            if (map[i][j]) used[map[i][j]] = 1;
            else {
                for (int k = 0; k < sum[i][j]; k++)
                    used[avai[i][j][k]] = 1;
            }
        }

        for (int k = 1; k <= 9; k++)
            if (!used[k]) return 0;
    }

    return 1;
}

/*
 * int checkPut(int x, int y)
 * {
 *     if (row[x] == 0 || col[y] == 0) return 1;
 * 
 *     memset(used, 0, sizeof(used));
 *     for (int j = 0; j < 9; j++) {
 *         int i = x;
 *         if (map[i][j]) used[map[i][j]] = 1;
 *         else {
 *             for (int k = 0; k < sum[i][j]; k++)
 *                 used[avai[i][j][k]] = 1;
 *         }
 *     }
 *     for (int k = 1; k <= 9; k++)
 *         if (!used[k]) return 0;
 * 
 *     memset(used, 0, sizeof(used));
 *     for (int i = 0; i < 9; i++) {
 *         int j = y;
 *         if (map[i][j]) used[map[i][j]] = 1;
 *         else {
 *             for (int k = 0; k < sum[i][j]; k++)
 *                 used[avai[i][j][k]] = 1;
 *         }
 *     }
 *     for (int k = 1; k <= 9; k++)
 *         if (!used[k]) return 0;
 * 
 *     return 1;
 * }
 */

int dfs(int, int);

int extend(int x, int y, int c)
{
    map[x][y] = c;
    space--;
    row[x]--;
    col[y]--;

/*
 *     if (checkPut(x, y)) {
 *         int _sum[10][10], _avai[10][10][10];
 *         memcpy(_sum, sum, sizeof(sum));
 *         memcpy(_avai, avai, sizeof(avai));
 */

        if (dfs(x, y)) return 1;

/*
 *         memcpy(avai, _avai, sizeof(avai));
 *         memcpy(sum, _sum, sizeof(sum));
 *     }
 */

    map[x][y] = 0;
    space++;
    row[x]++;
    col[y]++;

    return 0;
}

int dfs(int px, int py)
{
    if (space == 0) {
        printSudoku();
        return 1;
    }

    int min = 0x3FFFFFFF, x, y;

    for (int i = 0; i < 9; i++) {
        int j = py;
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

    for (int j = 0; j < 9; j++) {
        int i = px;
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

    for (int i = 0; i < 9; i++) {
        if (i == px) continue;
        for (int j = 0; j < 9; j++) {
            if (j == py) continue;

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
    }

    if (min == 0x3FFFFFFF) return 0;

    if (!checkMap()) return 0;

    for (int i = 0; i < min; i++)
        if (extend(x, y, avai[x][y][i])) return 1;

    return 0;
}

int main()
{
//    srand(time(0));

    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        space = 0;
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                char c;
                scanf(" %c", &c);
                if (c == '0') {
                    map[i][j] = 0;
                    space++;
                    row[i]++;
                    col[j]++;
                }
                else map[i][j] = c - '0';
            }

/*
 *         for (int i = 0; i < 9; i++)
 *             for (int j = 0; j < 9; j++) {
 *                 if (map[i][j] == 0)
 *                     sum[i][j] = checkPoint(i, j);
 *                 else sum[i][j] = 0;
 *             }
 */

/*
 *         int x, y;
 *         do {
 *             x = rand() % 9;
 *             y = rand() % 9;
 *         } while (map[x][y] == 0) ;
 * 
 *         dfs(x, y);
 */
        dfs(0, 0);
    }

    return 0;
}
