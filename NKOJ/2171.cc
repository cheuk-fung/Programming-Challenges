/*
 *  SRC: NKOJ 2171
 * PROB: Fair Division
 * ALGO: NULL
 * DATE: Aug 24, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;
using std::min;

int p, n, pay[100];

struct People {
    int max, id;

    bool operator <(const People& other) const
    {
        if (max != other.max) return max < other.max;
        else return id > other.id;
    }
} peo[100];

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) {
        int sum = 0;
        scanf("%d%d", &p, &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &peo[i].max);
            peo[i].id = i;
            sum += peo[i].max;
        }
        if (sum < p) {
            puts("IMPOSSIBLE");
            continue;
        }

        sort(peo, peo + n);

        for (int i = 0; i < n; i++) {
            pay[peo[i].id] = min(peo[i].max, p / (n - i));
            p -= pay[peo[i].id];
        }

        for (int i = 0; i < n - 1; i++) printf("%d ", pay[i]);
        printf("%d\n", pay[n - 1]);
    }

    return 0;
}
