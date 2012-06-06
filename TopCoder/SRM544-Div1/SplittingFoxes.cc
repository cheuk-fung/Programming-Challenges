#include <cstring>

const long long MOD = 1000000007;

class SplittingFoxes {
    private:
        struct Matrix {
            long long mat[4][4];

            Matrix() { memset(mat, 0, sizeof(mat)); }
            Matrix(long long S, long long L, long long R)
            {
                long long _mat[4][4] = {
                    {S - L - R,     0,     0,                 0},
                    {        0,     S, L - R,                 0},
                    {        S, R - L,     S,                 0},
                    {        0,     S,     0, (S + L + R) % MOD}
                };
                memmove(mat, _mat, sizeof(mat));
            }

            Matrix &operator*=(const Matrix &B)
            {
                Matrix C;
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        for (int k = 0; k < 4; k++)
                            C.mat[i][j] += mat[i][k] * B.mat[k][j] % MOD;
                memmove(mat, C.mat, sizeof(mat));

                return *this;
            }
        };

    public:
        int sum(long long n, int S, int L, int R)
        {
            Matrix A(S, L, R), B(S, L, R);

            n--;
            while (n) {
                if (n & 1) A *= B;
                B *= B;
                n >>= 1;
            }

            return (A.mat[3][0] % MOD + MOD) % MOD;
        }
};

