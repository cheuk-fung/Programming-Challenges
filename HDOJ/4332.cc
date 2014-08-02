/*
 *  SRC: HDOJ 4332
 * PROB: Constructing Chimney
 * ALGO: DP
 * DATE: Aug 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
const int MAXBIT = 1 << 8;

int F[MAXBIT], G[MAXBIT];

class Matrix {
    public:
        long long M[MAXBIT][MAXBIT];

        Matrix &operator*=(Matrix &) ;
} Zero, T[32], R;

Matrix &Matrix::operator*=(Matrix &O)
{
    memset(R.M, 0, sizeof R.M);
    for (int i = 0; i < MAXBIT; i++) {
        for (int j = 0; j < MAXBIT; j++) {
            for (int k = 0; k < MAXBIT; k++) {
                R.M[i][j] = (R.M[i][j] + M[i][k] * O.M[k][j]) % MOD;
            }
        }
    }
    memcpy(M, R.M, sizeof M);
    return *this;
}

void dfs(int orig, int curr, int next)
{
    if (curr == MAXBIT - 1) {
        Zero.M[orig][next] = 1;
        return ;
    }

    for (int i = 0; i < 8; i++) {
        if ((curr & (1 << i)) == 0) {
            assert((next & (1 << i)) == 0);
            dfs(orig, curr | (1 << i), next | (1 << i));
        }
    }

    for (int i = 0; i < 8; i++) {
        int j = (i + 1) % 8;
        if ((curr & (1 << i)) == 0 && (curr & (1 << j)) == 0) {
            assert((next & (1 << i)) == 0);
            assert((next & (1 << j)) == 0);
            dfs(orig, curr | (1 << i) | (1 << j), next);
        }
    }
}

int calc(int n)
{
    memset(F, 0, sizeof F);
    F[0] = 1;
    for (int cnt = 1; n; n >>= 1, cnt++) {
        if (n & 1) {
            memset(G, 0, sizeof G);
            for (int i = 0; i < MAXBIT; i++) {
                for (int j = 0; j < MAXBIT; j++) {
                    G[j] = (G[j] + F[i] * T[cnt].M[i][j]) % MOD;
                }
            }
            memcpy(F, G, sizeof F);
        }
    }

    return F[0];
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < MAXBIT; i++) {
        dfs(i, i, 0);
    }
    Zero.M[0][0] = 2;

    T[1] = Zero;
    for (int i = 2; i < 32; i++) {
        T[i] = T[i - 1];
        T[i] *= T[i - 1];
    }

    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        int r = calc(n);
        printf("Case %d: %d\n", task, r);
    }

    return 0;
}

