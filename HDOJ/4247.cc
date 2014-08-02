/*
 *  SRC: HDOJ 4747
 * PROB: A Famous ICPC Team
 * ALGO: NULL
 * DATE: Jul 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

int main()
{
    int task = 1;
    int a[4];
    while (~scanf("%d%d%d%d", a, a + 1, a + 2, a + 3)) {
        sort(a, a + 4);
        printf("Case %d: %d\n", task++, a[3] + a[2]);
    }

    return 0;
}

