/*
 *  SRC: HDOJ 4004
 * PROB: The Frog's Games
 * ALGO: Bisection
 * DATE: Sep 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int n, m, L;
int stone[500010];

bool check(int len)
{
    int cnt = 0, x = 0;
    for ( ; x < L && cnt < m; cnt++) {
        if (x + len >= L) return true;
        int *pos = upper_bound(stone, stone + n, x + len);
        if (pos == stone) return false;
        x = *(pos - 1);
    }
    return false;
}

int main()
{
    while (~scanf("%d%d%d", &L, &n, &m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", stone + i);
        }
        sort(stone, stone + n);

        int l = 0, r = L;
        while (l < r) {
            int mid = (l + r - 1) >> 1;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }

        printf("%d\n", l);
    }

    return 0;
}

