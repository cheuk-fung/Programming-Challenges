/*
 *  SRC: POJ
 * TASK: Who's in the Middle
 * ALGO: sort
 * DATE: Nov. 4, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int cow[n];
    for (int i = 0; i < n; i++) scanf("%d", &cow[i]);

    sort(cow, cow + n);

    printf("%d\n", cow[n / 2]);

    return 0;
}

