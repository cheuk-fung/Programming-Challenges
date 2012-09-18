/*
 *  SRC: HDOJ 4112
 * PROB: Break the Chocolate
 * ALGO: Math
 * DATE: Sep 18, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        printf("Case #%d: %I64d %d\n", task, (long long)n * m * k - 1, (int)(ceil(log2(n)) + ceil(log2(m)) + ceil(log2(k))));
    }

    return 0;
}

