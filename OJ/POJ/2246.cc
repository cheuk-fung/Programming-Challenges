/*
 *  SRC: POJ 2246
 * PROB: Matrix Chain Multiplication
 * ALGO: String
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>

int n, sig;

struct Matrix {
    int row, col;
    long long cnt;
};
Matrix mat[255];

bool multiply(Matrix& a, Matrix& b)
{
    if (a.col != b.row) {
        char c;
        while ((c = getchar()) != '\n') ;
        sig = 1;
        return false;
    }
    a.cnt += a.row * a.col * b.col + b.cnt;
    a.col = b.col;
    return true;
}

Matrix calc()
{
    char c = getchar();
    if (c == EOF) exit(0);

    Matrix res;
    res.row = 0;
    res.col = 0;
    res.cnt = 0;
    while (1 + 1 == 2) {
        if (c == '(') {
            Matrix t = calc();
            if (sig) return res;

            if (res.row == 0) res = t;
            else if (!multiply(res, t)) return res;

            c = getchar();
            continue;
        }
        if (c == ')') return res;
        if (c == '\n') return res;

        if (res.row == 0) res = mat[c];
        else if (!multiply(res, mat[c])) return res;

        c = getchar();
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char m[5];
        int r, c;
        scanf("%s%d%d", m, &r, &c);
        mat[m[0]].row = r;
        mat[m[0]].col = c;
        mat[m[0]].cnt = 0;
    }
    getchar();

    while (1 + 1 == 2) {
        sig = 0;
        Matrix res = calc();

        if (sig) puts("error");
        else printf("%lld\n", res.cnt);
    }

    return 0;
}

