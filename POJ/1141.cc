/*
 *  SRC: POJ 1141
 * PROB: Brackets Sequence
 * ALGO: DP
 * DATE: Jul 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

const int MAXINT = 0x3FFFFFFF;

#include <cstdio>
#include <cstring>

char b[110];
int f[110][110];
char g[110][110][220];

void makePair(char c, char* s)
{
    if (c == '(' || c == ')') {
        *s++ = '(';
        *s = ')';
        return ;
    }

    *s++ = '[';
    *s = ']';
}

int isPair(char a, char b)
{
    if (a == '(' && b == ')') return 1;
    if (a == '[' && b == ']') return 1;
    return 0;
}

int solve(int x, int y)
{
    if (f[x][y] != MAXINT) return f[x][y];
    
    if (x == y) {
        makePair(b[x], g[x][y]);
        g[x][y][2] = '\0';

        return f[x][y] = 1;
    }

    if (x + 1 == y) {
        if (isPair(b[x], b[y])) {
            makePair(b[x], g[x][y]);
            g[x][y][2] = '\0';

            return f[x][y] = 0;
        }
        else {
            makePair(b[x], g[x][y]);
            makePair(b[y], g[x][y] + 2);
            g[x][y][4] = '\0';

            return f[x][y] = 2;
        }
    }

    if (isPair(b[x], b[y])) {
        f[x][y] = solve(x + 1, y - 1);

        g[x][y][0] = b[x];
        strcpy(g[x][y] + 1, g[x + 1][y - 1]);
        int len = strlen(g[x][y]);
        g[x][y][len] = b[y];
        g[x][y][len + 1] = '\0';
    }

    int minK = -1;;
    for (int k = x; k < y; k++) {
        int c1 = solve(x, k);
        int c2 = solve(k + 1, y);

        if (c1 + c2 < f[x][y]) {
            f[x][y] = c1 + c2;
            minK = k;
        }
    }
    if (minK != -1) {
        strcpy(g[x][y], g[x][minK]);
        strcpy(g[x][y] + strlen(g[x][y]), g[minK + 1][y]);
    }

    return f[x][y];
}

int main()
{
    while (gets(b)) {

        int n = strlen(b);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                f[i][j] = MAXINT;

        solve(0, n - 1);

        printf("%s\n", g[0][n - 1]);
    }

    return 0;
}
