/*
 *  SRC: NKOJ p1856
 * PROB: Best Messenger Tool——NKQQ
 * ALGO: Bisection
 * DATE: Jul 13, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

int Lev[] = {0, 100, 500, 2000, 10000, 50000, 200000};

int n, q, score[100010];

bool check(int p, int d, int l)
{
    return score[p] + d > Lev[l - 1];
}

int bisection(int d, int l)
{
    int low = 0, high = n;
    while (low < high) {
        int mid = (low + high - 1) / 2;
        if (check(mid, d, l)) high = mid;
        else low = mid + 1;
    }

    return low;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", score + i);

    sort(score, score + n);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int d, l;
        scanf("%d%d", &d, &l);
        if (d >= 200000) {
            printf("%d\n", n);
            continue;
        }

        int low = 0, high = n;
        if (l > 1) low = bisection(d, l);
        if (l < 7) high = bisection(d, l + 1);
        printf("%d\n", high - low);
    }
}
