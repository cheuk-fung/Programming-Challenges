/*
 *  SRC: POJ 3233
 * PROB: Matrix Power Series
 * ALGO: Matrix
 * DATE: Aug 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

int MOD;

class Matrix {
    public:
        int n;
        long long a[30][30];

        Matrix(int _n) : n(_n) { memset(a, 0, sizeof a); }

        Matrix operator*(const Matrix &M) const
        {
            Matrix R(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        R.a[i][j] = (R.a[i][j] + a[i][k] * M.a[k][j]) % MOD;
                    }
                }
            }
            return R;
        }

        Matrix operator^(int k) const
        {
            Matrix R = *this;
            Matrix T = *this;
            for (k--; k; k >>= 1) {
                if (k & 1) R = R * T;
                T = T * T;
            }
            return R;
        }

        Matrix operator+(const Matrix &M) const
        {
            Matrix R(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    R.a[i][j] = (a[i][j] + M.a[i][j]) % MOD;
                }
            }
            return R;
        }

        Matrix sum(int k) const
        {
            int bcnt = 31;
            while ((k >> bcnt) == 0) bcnt--;
            Matrix R = *this, M = *this;
            for (int i = bcnt - 1; i >= 0; i--) {
                if (k & (1 << i)) {
                    R = R + M * R + M * M * *this;
                    M = M * M * *this;
                } else {
                    R = R + M * R;
                    M = M * M;
                }
            }
            return R;
        }
};

int main()
{
    int n, k;
    while (~scanf("%d%d%d", &n, &k, &MOD)) {
        Matrix A(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lld", &A.a[i][j]);
            }
        }

        Matrix R = A.sum(k);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%lld%c", R.a[i][j], j + 1 == n ? '\n' : ' ');
            }
        }
    }

    return 0;
}

