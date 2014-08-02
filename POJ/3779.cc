/*
 *  SRC: POJ 3779
 * PROB: Single CPU, multi-tasking
 * ALGO: Implementation
 * DATE: Oct 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-10;

double T[110];
double ans[110];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf", &T[i]);
        }

        double now = 0;
        for (int i = 0; i < n; i++) {
            int min_time = 0x3f3f3f3f;
            for (int j = 0; j < n; j++) {
                if (T[j] <= 0) continue;
                min_time = min(min_time, (int)(T[j] - eps));
            }
            for (int j = 0; j < n; j++) {
                if (T[j] <= 0) continue;
                T[j] -= min_time;
                now += min_time;
            }
            for (int j = 0; j < n; j++) {
                if (T[j] <= 0) continue;
                if (T[j] <= 1) {
                    now += T[j];
                    ans[j] = now;
                    T[j] = 0;
                } else {
                    T[j] -= 1;
                    now += 1;
                }
            }
        }

        printf("Case %d:\n", task);
        for (int i = 0; i < n; i++) printf("%.2f\n", ans[i]);
    }

    return 0;
}

