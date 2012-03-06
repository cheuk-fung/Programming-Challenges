/*
 *  SRC: POJ 2151
 * PROB: Check the difficulty of problems
 * ALGO: DP
 * DATE: Mar 06, 2012
 * COMP: c++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

double p[1010][50];
double f[50][50];

int main()
{
    while (true) {
        int m, T, n;
        cin >> m >> T >> n;
        if (m == 0 && T == 0 && n == 0) break;
        for (int i = 0; i < T; i++)
            for (int j = 1; j <= m; j++)
                cin >> p[i][j];

        double atLeastOne = 1;
        double lessThanN = 1;
        for (int t = 0; t < T; t++) {
            f[0][0] = 1;
            for (int i = 1; i <= m; i++) {
                f[i][0] = f[i - 1][0] * (1 - p[t][i]);
                f[i][i] = f[i - 1][i - 1] * p[t][i];
                for (int j = 1; j < i; j++) {
                    f[i][j] = f[i - 1][j - 1] * p[t][i] + f[i - 1][j] * (1 - p[t][i]);
                }
            }
            atLeastOne *= 1 - f[m][0];
            double sum = 0;
            for (int i = 1; i < n; i++) {
                sum += f[m][i];
            }
            lessThanN *= sum;
        }

        printf("%.3lf\n", atLeastOne - lessThanN);
    }

    return 0;
}
