/*
 *  SRC: NKOJ
 * TASK: Just a game
 * ALGO: DFS
 * DATE: 03/30/2011 
 *
 * Created by Leewings Ac
 */

#include        <cstdio>
#include	<vector>

using namespace std;

struct Point {
    int x, y;

    Point(int xx, int yy) : x(xx), y(yy) { }
};

char board[5][5];

inline bool row(const char ch, const int x, const int y)
{
    switch(y) {
        case 0:
            if (board[x][1] == ch && board[x][2] == ch) return true; // [_TT*]
            break;
        case 1:                            
            if (board[x][0] == ch && board[x][2] == ch) return true; // [T_T*]
            if (board[x][2] == ch && board[x][3] == ch) return true; // [*_TT]
            break;
        case 2:                            
            if (board[x][0] == ch && board[x][1] == ch) return true; // [TT_*]
            if (board[x][1] == ch && board[x][3] == ch) return true; // [*T_T]
            break;
        case 3:                            
            if (board[x][1] == ch && board[x][2] == ch) return true; // [*TT_]
    }
    return false;
}

inline bool col(const char ch, const int x, const int y)
{
    switch(x) {
        case 0:
            if (board[1][y] == ch && board[2][y] == ch) return true; // [_TT*]'
            break;
        case 1:
            if (board[0][y] == ch && board[2][y] == ch) return true; // [T_T*]'
            if (board[2][y] == ch && board[3][y] == ch) return true; // [*_TT]'
            break;
        case 2:
            if (board[0][y] == ch && board[1][y] == ch) return true; // [TT_*]'
            if (board[1][y] == ch && board[3][y] == ch) return true; // [*T_T]'
            break;
        case 3:
            if (board[1][y] == ch && board[2][y] == ch) return true; // [*TT_]'
    }
    return false;
}

inline bool diag(const char ch, const int x, const int y, const int dy)
{
    if (dy == 1) {
        if (x - y < -1 || x - y > 1) return false;
    }
    else {
        if (x + y < 2 || x + y > 4) return false;
    }
    switch(x) {
        case 0:
            if (board[1][y + dy] == ch && board[2][y + 2 * dy] == ch) return true;
            break;
        case 1:
            if (y - dy >= 0 && y - dy < 4)
                if (board[0][y - dy] == ch && board[2][y + dy] == ch) return true;
            if (y + 2 * dy >= 0 && y + 2 * dy < 4)
                if (board[2][y + dy] == ch && board[3][y + 2 * dy] == ch) return true;
            break;
        case 2:
            if (y - 2 * dy >= 0 &&  y - 2 * dy < 4)
                if (board[0][y - 2 * dy] == ch && board[1][y - dy] == ch) return true;
            if (y + dy >= 0 && y + dy < 4)
                if (board[1][y - dy] == ch && board[3][y + dy] == ch) return true;
            break;
        case 3:
            if (board[1][y - 2 * dy] == ch && board[2][y - dy] == ch) return true;
    }
    return false;
}

inline int winPoint(const char ch, vector<Point>* vec)
{
    int res = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == '_')
                if (row(ch, i, j) || col(ch, i, j) || diag(ch, i, j, 1) || diag(ch, i, j, -1)) {
                    res++;
                    vec->push_back(Point(i, j));
                }
    return res;
}

int next(const char a, const char b)
{
    vector<Point> qVec;
    int q = winPoint(b, &qVec);
    if (q > 1) return -1; // Lose
    if (q == 1) {
        board[qVec[0].x][qVec[0].y] = a;
        return -next(b, a);
    }
    // q == 0
    bool canNotPut = true;
    vector<Point> pVec;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == '_') {
                canNotPut = false;
                board[i][j] = a;
                int p = winPoint(a, &pVec);
                if (p > 1) return 1; //Win
                board[i][j] = '_';
            }
    if (canNotPut) return 0; // Draw

    bool canDraw = false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == '_') {
                board[i][j] = a;
                int res = -next(b, a);
                if (res > 0) return 1; // Win
                if (res == 0) canDraw = true;
                board[i][j] = '_';
            }
        }
    if (canDraw) return 0; // Draw
    return -1; // Lose
}

int work(const char a, const char b)
{
    vector<Point> pVec;
    int p = winPoint(a, &pVec);
    if (p) return p; // Win
    else return next(a, b);
}

int main()
{
    int xsum, osum;
    xsum = osum = 0;
    for (int i = 0; i < 4; i++) {
        scanf("%s", board[i]);
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 'X') xsum++;
            else if (board[i][j] == 'O') osum++;
        }
    }

    int status;
    if (xsum == osum) status = work('X', 'O');
    else status = work('O', 'X');
    if (status > 0) printf("Win\n");
    else if (status == 0) printf("Draw\n");
    else printf("Lose\n");

    return 0;
}				/* ----------  end of function main  ---------- */

