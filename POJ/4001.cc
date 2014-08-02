/*
 *  SRC: POJ 4001
 * PROB: Xiangqi
 * ALGO: Implementation
 * DATE: Sep 21, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

const int N = 11, M = 10;

struct Piece {
    char type;
    int x, y;
} red[10], bg;

char mat[N][M];
bool available[N][M];

void general(const Piece &p)
{
    for (int x = p.x - 1, y = p.y; x > 0; x--) {
        available[x][y] = false;
        if (mat[x][y] != '.') break;
    }
}

void chariot(const Piece &p)
{
    for (int x = p.x - 1, y = p.y; x > 0; x--) {
        available[x][y] = false;
        if (mat[x][y] != '.') break;
    }
    for (int x = p.x + 1, y = p.y; x < N; x++) {
        available[x][y] = false;
        if (mat[x][y] != '.') break;
    }
    for (int x = p.x, y = p.y - 1; y > 0; y--) {
        available[x][y] = false;
        if (mat[x][y] != '.') break;
    }
    for (int x = p.x, y = p.y + 1; y < M; y++) {
        available[x][y] = false;
        if (mat[x][y] != '.') break;
    }
}

void horse(const Piece &p)
{
    int x = p.x, y = p.y;
    if (x - 2 > 0 && mat[x - 1][y] == '.') available[x - 2][y - 1] = available[x - 2][y + 1] = false;
    if (x + 2 < N && mat[x + 1][y] == '.') available[x + 2][y - 1] = available[x + 2][y + 1] = false;
    if (y - 2 > 0 && mat[x][y - 1] == '.') available[x - 1][y - 2] = available[x + 1][y - 2] = false;
    if (y + 2 < M && mat[x][y + 1] == '.') available[x - 1][y + 2] = available[x + 1][y + 2] = false;
}

void cannon(const Piece &p)
{
    for (int x = p.x - 1, y = p.y; x > 0; x--) {
        if (mat[x][y] != '.') {
            for (int xx = x - 1, yy = p.y; xx > 0; xx--) {
                available[xx][yy] = false;
                if (mat[xx][yy] != '.') break;
            }
            break;
        }
    }
    for (int x = p.x + 1, y = p.y; x < N; x++) {
        if (mat[x][y] != '.') {
            for (int xx = x + 1, yy = p.y; xx < N; xx++) {
                available[xx][yy] = false;
                if (mat[xx][yy] != '.') break;
            }
            break;
        }
    }
    for (int x = p.x, y = p.y - 1; y > 0; y--) {
        if (mat[x][y] != '.') {
            for (int xx = p.x, yy = y - 1; yy > 0; yy--) {
                available[xx][yy] = false;
                if (mat[xx][yy] != '.') break;
            }
            break;
        }
    }
    for (int x = p.x, y = p.y + 1; y < M; y++) {
        if (mat[x][y] != '.') {
            for (int xx = p.x, yy = y + 1; yy < M; yy++) {
                available[xx][yy] = false;
                if (mat[xx][yy] != '.') break;
            }
            break;
        }
    }
}

int main()
{
    int n;
    while (scanf("%d%d%d", &n, &bg.x, &bg.y), n || bg.x || bg.y) {
        memset(mat, '.', sizeof mat);
        memset(available, true, sizeof available);
        for (int i = 0; i < n; i++) {
            scanf(" %c %d%d", &red[i].type, &red[i].x, &red[i].y);
            mat[red[i].x][red[i].y] = red[i].type;
        }

        for (int i = 0; i < n; i++) {
            switch (red[i].type) {
                case 'G': general(red[i]); break;
                case 'R': chariot(red[i]); break;
                case 'H': horse(red[i]); break;
                case 'C': cannon(red[i]);
            }
        }

        bool checkmate = true;
        if (0 < bg.x - 1 && available[bg.x - 1][bg.y]) checkmate = false;
        if (bg.x + 1 < 4 && available[bg.x + 1][bg.y]) checkmate = false;
        if (3 < bg.y - 1 && available[bg.x][bg.y - 1]) checkmate = false;
        if (bg.y + 1 < 7 && available[bg.x][bg.y + 1]) checkmate = false;
        puts(checkmate ? "YES" : "NO");
    }

    return 0;
}

