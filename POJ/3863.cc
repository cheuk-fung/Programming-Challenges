/*
 *  SRC: POJ 3863
 * PROB: Business Center
 * ALGO: NULL
 * DATE: Mar 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::min;

const int INF = 0x3f3f3f3f;

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    int ans = INF;
    for (int i = 0; i < m; i++) {
        int u, d;
        scanf("%d%d", &u, &d);
        int u_cnt = ceil((double)d * n / (u + d));
        int lowest = (u + d) * u_cnt - d * n;
        ans = min(ans, lowest ? lowest : u + d);
    }

    printf("%d\n", ans);

    return 0;
}

