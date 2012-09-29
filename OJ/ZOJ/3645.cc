/*
 *  SRC: ZOJ 3645
 * PROB: BiliBili
 * ALGO: Gauss elimination
 * DATE: Sep 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-8;

inline bool eq0(double x) { return fabs(x) < eps; }

double X[11];

//  1: infinitely many solutions
//  0: one solution
// -1: no solution
int solve(double A[11][11], double B[11])
{
    int n = 11;

    for (int xc = 0; xc < n; xc++) {
        int row = xc;
        if (eq0(A[row][xc])) {
            for (int i = row + 1; i < n; i++) {
                if (!eq0(A[i][xc])) {
                    row = i;
                    break;
                }
            }
        }
        if (eq0(A[row][xc])) {
            if (eq0(B[row])) return 1;
            return -1;
        }

        if (row != xc) {
            swap_ranges(A[xc], A[xc] + n, A[row]);
            swap(B[xc], B[row]);
        }

        for (int i = xc + 1; i < n; i++) {
            double rate = A[i][xc] / A[xc][xc];
            for (int j = xc; j < n; j++) {
                A[i][j] -= rate * A[xc][j];
            }
            B[i] -= rate * B[xc];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        X[i] = B[i];
        for (int j = n - 1; j > i; j--) {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }

    return 0;
}

double A[11][11], B[11];
double first[12];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        for (int i = 0; i < 12; i++) scanf("%lf", first + i);
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) scanf("%lf", A[i] + j);
            scanf("%lf", B + i);
            B[i] = B[i] * B[i] - first[11] * first[11];
            for (int j = 0; j < 11; j++) {
                B[i] += first[j] * first[j] - A[i][j] * A[i][j];
                A[i][j] = 2 * (first[j] - A[i][j]);
            }
        }

        solve(A, B);
        for (int i = 0; i < 10; i++) printf("%.2f ", X[i]);
        printf("%.2f\n", X[10]);
    }

    return 0;
}

