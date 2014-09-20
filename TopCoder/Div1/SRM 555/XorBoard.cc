const int MOD = 555555555;
const int MAXC = 1555 << 1;
int C[MAXC][MAXC];

class XorBoard {
    private:

    public:
        int count(int H, int W, int Rcount, int Ccount, int S)
        {
            C[0][0] = 1;
            for (int i = 1; i < MAXC; i++) {
                C[i][0] = C[i][i] = 1;
                for (int j = 1; j < i; j++) {
                    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
                }
            }

            int res = 0;
            for (int r = 0; r <= H && r <= Rcount; r++) {
                for (int c = 0; c <= W && c <= Ccount; c++) {
                    if ((Rcount - r) % 2 == 1) continue;
                    if ((Ccount - c) % 2 == 1) continue;
                    int tot = r * W + H * c - 2 * r * c;
                    if (tot != S) continue;
                    int tr = (Rcount - r) / 2;
                    int tc = (Ccount - c) / 2;
                    res = (res + (long long)C[H][r] * C[tr + H - 1][tr] % MOD * C[W][c] % MOD * C[tc + W - 1][tc] % MOD) % MOD;
                }
            }

            return res;
        }
};
