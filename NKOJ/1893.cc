/*
 *  SRC: NKOJ 1893
 * PROB: 统计数字
 * ALGO: sort
 * DATE: Aug 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

int n, a[200001];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    a[n] = 1500000001;
    for (int i = 1, cnt = 1, prev = a[0]; i <= n; i++) {
        if (a[i] != prev) {
            printf("%d %d\n", prev, cnt);
            cnt = 1;
            prev = a[i];
        }
        else cnt++;
    }

    return 0;
}
