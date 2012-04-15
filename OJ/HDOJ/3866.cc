/*
 *  SRC: HDOJ 3866
 * PROB: Moonfang's Birthday
 * ALGO: Greedy
 * DATE: Apr 15, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

struct People {
    int money, id;
    int contribute;
};
People peo[10010];

bool cmp_money(const People &a, const People &b)
{
    if (a.money == b.money) {
        return a.id > b.id;
    }
    return a.money < b.money;
}

bool cmp_id(const People &a, const People &b)
{
    return a.id < b.id;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int p, n;
        scanf("%d%d", &p, &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &peo[i].money);
            peo[i].id = i;
        }
        sort(peo, peo + n, cmp_money);

        for (int i = 0; i < n; i++) {
            int avg = p / (n - i);
            if (peo[i].money > avg) {
                peo[i].contribute = avg;
                p -= avg;
            } else {
                peo[i].contribute = peo[i].money;
                p -= peo[i].money;
            }
        }
        sort(peo, peo + n, cmp_id);

        if (p) {
            puts("IMPOSSIBLE");
        } else {
            for (int i = 0; i < n - 1; i++) {
                printf("%d ", peo[i].contribute);
            }
            printf("%d\n", peo[n - 1].contribute);
        }
    }

    return 0;
}

