/*
 *  SRC: NKOJ
 * TASK: 分數線劃定
 * ALGO: sort
 * DATE: 03/22/2011
 *
 * Created by Leewings Ac
 */

#include <cstdio>

using namespace std;

struct Player {
    int id, s;
};

void swap(Player& a, Player& b)
{
    Player c = a;
    a = b;
    b = c;
}

void qsort(Player* p, int l, int r)
{
    Player mid = p[(l + r) / 2];
    int i = l, j = r;
    while (i < j) {
        while (p[i].s > mid.s || (p[i].s == mid.s && p[i].id < mid.id)) i++;
        while (p[j].s < mid.s || (p[j].s == mid.s && p[j].id > mid.id)) j--;
        if (i <= j) swap(p[i++], p[j--]);
    }
    if (i < r) qsort(p, i, r);
    if (l < j) qsort(p, l, j);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    Player p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &p[i].id, &p[i].s);
    }
    qsort(p, 0, n - 1);
//    for (int i = 0; i < n; i++) {
//        printf("%d %d\n", p[i].id, p[i].s);
//    }

    int sum = int(m * 1.50);
    int l = p[sum - 1].s;
    while (p[sum].s == l) sum++;
    printf("%d %d\n", l, sum);
    for (int i = 0; i < sum; i++) {
        printf("%d %d\n", p[i].id, p[i].s);
    }

    return 0;
}

