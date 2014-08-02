/*
 *  SRC: HDOJ 4405
 * PROB: Aeroplane chess
 * ALGO: DP
 * DATE: Sep 22, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

double P[100010], E[100010];
int flyto[100010];
pair<int, int> flightlines[1010];

int main()
{
    while (true) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;

        for (int i = 0; i < m; i++) {
            scanf("%d%d", &flightlines[i].first, &flightlines[i].second);
        }
        sort(flightlines, flightlines + m);

        for (int i = 1; i <= n; i++) flyto[i] = i;
        for (int i = m - 1; i >= 0; i--) {
            flyto[flightlines[i].first] = flyto[flightlines[i].second];
        }

        memset(P, 0, sizeof P);
        memset(E, 0, sizeof E);
        P[0] = 1;
        for (int i = 0; i < n; i++) {
            if (flyto[i] != i) continue;
            for (int j = 1; j <= 6; j++) {
                int next = i + j > n ? n : i + j;
                P[flyto[next]] += P[i] / 6;
                E[flyto[next]] += (E[i] + P[i]) / 6;
            }
        }

        printf("%.4f\n", E[n]);
    }
}
