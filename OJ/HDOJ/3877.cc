/*
 *  SRC: HDOJ 3877
 * PROB: Special sort
 * ALGO: NULL
 * DATE: May 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

#ifdef ONLINE_JUDGE
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

struct Equation {
    long long a, b, c;
    int sig;
    int id;

    bool operator<(const Equation &o) const
    {
        return c == o.c ? sig == o.sig ? id < o.id : sig > o.sig : c > o.c;
    }
} equa[10000];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf(LLD""LLD, &equa[i].a, &equa[i].b);
            equa[i].c = equa[i].a + equa[i].b;
            equa[i].sig = (equa[i].a == equa[i].b ? 0 : equa[i].a > equa[i].b ? 1 : -1);
            equa[i].id = i;
        }
        sort(equa, equa + n);
        for (int i = 0; i < n; i++) {
            printf(LLD"+"LLD"=[%c"LLD"]\n", equa[i].a, equa[i].b, equa[i].sig == 0 ? '=' : equa[i].sig > 0 ? '>' : '<', equa[i].c);
        }
        putchar(10);
    }

    return 0;
}

