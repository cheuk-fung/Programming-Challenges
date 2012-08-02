/*
 *  SRC: HDOJ 4334
 * PROB: Trouble
 * ALGO: NULL
 * DATE: Aug 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXSIZE = 123451;

int n;
long long s[5][210];
set<long long> tryit[MAXSIZE];

bool check()
{
    for (int i = 0; i < MAXSIZE; i++) tryit[i].clear();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long t = s[0][i] + s[1][j];
            tryit[(t % MAXSIZE + MAXSIZE) % MAXSIZE].insert(t);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                long long t = -s[2][i] - s[3][j] - s[4][k];
                if (tryit[(t % MAXSIZE + MAXSIZE) % MAXSIZE].count(t)) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        scanf("%d", &n);
        for (int k = 0; k < 5; k++) {
            for (int i = 0; i < n; i++) {
                cin >> s[k][i];
                // scanf("%I64d", &s[k][i]);
            }
        }

        puts(check() ? "Yes" : "No");
    }

    return 0;
}
