/*
 *  SRC: HDOJ 3876
 * PROB: A pupil’s problem
 * ALGO: NULL
 * DATE: May 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        long long delta = (long long)b * b - 4ll * a * c;
        if (delta < 0) {
            puts("NO");
        } else if (delta == 0) {
            printf("%.2f\n", -b / (2.0 * a));
        } else {
            double x1 = (-b + sqrt(delta)) / (2.0 * a);
            double x2 = (-b - sqrt(delta)) / (2.0 * a);
            printf("%.2f %.2f\n", min(x1, x2), max(x1, x2));
        }
    }

    return 0;
}

