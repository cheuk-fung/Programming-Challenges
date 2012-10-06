/*
 *  SRC: ZOJ 3497
 * PROB: Mistwald
 * ALGO: Matrix
 * DATE: Oct 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

class Matrix {
    private:
        int n;

    public:
        long long mat[26][26];

        Matrix(int _n) : n(_n) { memset(mat, 0, sizeof mat); }

        Matrix operator*(const Matrix &B) const
        {
            Matrix R(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        R.mat[i][j] += mat[i][k] * B.mat[k][j];
                    }
                }
            }
            return R;
        }

        Matrix pow(int p) const
        {
            Matrix R = *this;
            Matrix M = *this;
            for (p--; p; p >>= 1) {
                if (p & 1) R = R * M;
                M = M * M;
            }
            return R;
        }
};

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);

        Matrix M(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int u = i * m + j;
                scanf(" (");
                for (int k = 0; k < 4; k++) {
                    int x, y;
                    scanf("(%d,%d)%*c", &x, &y);
                    int v = --x * m + --y;
                    M.mat[u][v] = 1;
                }
            }
        }
        int exiting = n * m - 1;
        for (int j = 0; j <= exiting; j++) {
            M.mat[exiting][j] = 0;
        }

        int q;
        scanf("%d", &q);
        while (q--) {
            int p;
            scanf("%d", &p);
            if (p == 0) {
                puts(n == 1 && m == 1 ? "True" : "False");
                continue;
            }
            Matrix R = M.pow(p);
            if (R.mat[0][exiting]) {
                int cnt = 0;
                for (int j = 0; j <= exiting; j++) {
                    if (R.mat[0][j]) {
                        cnt++;
                    }
                }
                puts(cnt == 1 ? "True" : "Maybe");
            } else {
                puts("False");
            }
        }

        putchar(10);
    }

    return 0;
}

