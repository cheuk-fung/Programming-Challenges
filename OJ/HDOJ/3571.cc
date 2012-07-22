/*
 *  SRC: HDOJ 4571
 * PROB: N-dimensional Sphere
 * ALGO: Gauss Elimination
 * DATE: Jul 22, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#ifdef ONLINE_JUDGE
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

const int MAXN = 55;
const long long MAXX = 100000000000000000ll;
const long long MOD = MAXX * 10 + 3;

long long line0[MAXN], sqrline0[MAXN];
long long A[MAXN][MAXN], B[MAXN], X[MAXN];

inline long long modnum(long long x)
{
    while (x >= MOD) x -= MOD;
    while (x < 0) x += MOD;
    return x;
}

long long modmul(long long a, long long b)
{
    long long r = 0;
    while (b) {
        if (b & 1) {
            r += a;
            if (r >= MOD) r -= MOD;
        }
        a <<= 1;
        if (a >= MOD) a -= MOD;
        b >>= 1;
    }
    return r;
}

long long moddiv(long long a, long long b)
{
    long long r = 1;
    for (long long power = MOD - 2; power; power >>= 1) {
        if (power & 1) r = modmul(r, b);
        b = modmul(b, b);
    }

    return modmul(a, r);
}

void gauss_elimination(int n)
{
    for (int xc = 0; xc < n; xc++) {
        int row = xc;
        if (!A[row][xc]) {
            for (int i = row + 1; i < n; i++) {
                if (A[i][xc]) {
                    row = i;
                    break;
                }
            }
        }

        if (row != xc) {
            swap_ranges(A[xc], A[xc] + n, A[row]);
        }

        for (int i = xc + 1; i < n; i++) {
            if (!A[i][xc]) continue;

            for (int j = xc + 1; j < n; j++) {
                A[i][j] = modnum(modmul(A[i][j], A[xc][xc]) - modmul(A[xc][j], A[i][xc]));
            }
            B[i] = modnum(modmul(B[i], A[xc][xc]) - modmul(B[xc], A[i][xc]));
            A[i][xc] = 0;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        X[i] = B[i];
        for (int j = n - 1; j > i; j--) {
            X[i] = modnum(X[i] - modmul(A[i][j], X[j]));
        }
        X[i] = moddiv(X[i], A[i][i]);
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf(LLD, &line0[i]);
            line0[i] = modnum(line0[i] + MAXX);
            sqrline0[i] = modmul(line0[i], line0[i]);
        }

        for (int i = 0; i < n; i++) {
            B[i] = 0;
            for (int j = 0; j < n; j++) {
                long long aij;
                scanf(LLD, &aij);
                aij = modnum(aij + MAXX);
                A[i][j] = modnum(2 * (aij - line0[j]));
                B[i] = modnum(B[i] + modnum(modmul(aij, aij) - sqrline0[j]));
            }
        }

        gauss_elimination(n);
        printf("Case %d:\n", task);
        for (int i = 0; i < n; i++) {
            printf(LLD"%c", X[i] - MAXX, i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}

