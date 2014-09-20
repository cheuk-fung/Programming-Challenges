#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int C[2002][2002];
int G[2002][2002];
int f[2002];

class Spacetsk {
    private:

    public:
        int countsets(int L, int H, int K)
        {
            if (K == 1) return (L + 1) * (H + 1);

            memset(C, 0, sizeof(C));
            memset(G, 0, sizeof(G));
            memset(f, 0, sizeof(f));

            C[0][0] = 1;
            for (int i = 1; i < max(L, H) + 2; i++) {
                C[i][0] = 1;
                for (int j = 1; j <= i; j++) {
                    C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
                    G[i][j] = G[j][i] = __gcd(i, j);
                }
            }

            f[0] = 0;
            for (int i = 1; i <= L; i++) {
                f[i] = f[i - 1];
                for (int j = 1; j <= H; j++) {
                    f[i] = ((f[i] + C[G[i][j] + 1][K] - C[G[i][j]][K]) % MOD + MOD) % MOD;
                }
            }

            int cnt = 0;
            for (int i = 0; i <= L; i++) {
                cnt = (cnt + C[H + 1][K]) % MOD;
                cnt = (cnt + f[i]) % MOD;
                cnt = (cnt + f[L - i]) % MOD;
            }

            return cnt;
        }
};

