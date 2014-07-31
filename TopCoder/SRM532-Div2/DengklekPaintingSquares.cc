#include <cstdio>
#include <cstring>

using namespace std;

int f[101][9][10000];

class DengklekPaintingSquares {
    private:
        static const int MOD = 1000000007;

        int pow3[9];

        int get(int x, int p) { return x / pow3[p] % 3; }
        int set(int x, int p, int v) { return x + (v - get(x, p)) * pow3[p]; }
        int calc(int *a, int b) { return *a = (*a + b) % MOD; }

    public:
        int numSolutions(int N, int M)
        {
            memset(f, 0, sizeof(f));

            pow3[0] = 1;
            for (int i = 1; i <= 8; i++)
                pow3[i] = 3 * pow3[i - 1];

            int start = 0;
            for (int j = 0; j < M; j++)
                start += 2 * pow3[j];

            f[0][0][start] = 1;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    for (int k = 0; k < pow3[M]; k++) {
                        /*  get(k, j) =
                         *      0: even
                         *      1: odd
                         *      2: not colored
                         */

                        if (get(k, j) != 1)
                            calc(&f[i][j + 1][set(k, j, 2)], f[i][j][k]);
                        if (get(k, j) != 0) {
                            int next = set(k, j, 0);
                            if (get(k, j) == 1) next = set(k, j, 1);
                            if (j > 0 && get(k, j - 1) != 2) {
                                next = set(next, j, get(next, j) ^ 1);
                                next = set(next, j - 1, get(next, j - 1) ^ 1);
                            }
                            calc(&f[i][j + 1][next], f[i][j][k]);
                        }
                    }
                }
                for (int k = 0; k < pow3[M]; k++)
                    f[i + 1][0][k] = f[i][M][k];
            }

            int res = 0;
            for (int k = 0; k < pow3[M]; k++) {
                bool flag = true;
                for (int j = 0; j < M; j++)
                    if (get(k, j) == 1) {
                        flag = false;
                        break;
                    }
                if (flag) calc(&res, f[N][0][k]);
            }

            return res;
        }
};
