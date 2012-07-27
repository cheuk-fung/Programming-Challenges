/*
 *  SRC: HDOJ 4310
 * PROB: Hero
 * ALGO: Gready
 * DATE: Jul 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Enemy {
    int dps, hp;

    bool operator <(const Enemy &o) const
    {
        return hp * o.dps < o.hp * dps;
    }
} e[100];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        int totdps = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &e[i].dps, &e[i].hp);
            totdps += e[i].dps;
        }
        sort(e, e + n);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += totdps * e[i].hp;
            totdps -= e[i].dps;
        }

        printf("%d\n", ans);
    }
    return 0;
}

