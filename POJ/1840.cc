/*
 *  SRC: POJ 1840
 * PROB: Eqs
 * ALGO: Bisection
 * DATE: Mar 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;
using std::lower_bound;
using std::upper_bound;

const int MOD = 1000000007;
const int MAX_IDX = 101 * 101 * 101;

int part[MAX_IDX];

int get_idx(int x1, int x2, int x3)
{
    return (x1 + 50) * 101 * 101 + (x2 + 50) * 101 + x3 + 50;
}

int pow3(int x)
{
    return x * x * x;
}

int main()
{
    int a1, a2, a3, a4, a5;
    scanf("%d%d%d%d%d", &a1, &a2, &a3, &a4, &a5);

    for (int x1 = -50; x1 <= 50; x1++) {
        for (int x2 = -50; x2 <= 50; x2++) {
            for (int x3 = -50; x3 <= 50; x3++) {
                int result;
                if (x1 == 0 || x2 == 0 || x3 == 0) result = 0x3f3f3f3f;
                else result = a1 * pow3(x1) + a2 * pow3(x2) + a3 * pow3(x3);
                part[get_idx(x1, x2, x3)] = result;
            }
        }
    }
    sort(part, part + MAX_IDX);

    int cnt = 0;
    for (int x4 = -50; x4 <= 50; x4++) {
        if (x4 == 0) continue;
        for (int x5 = -50; x5 <= 50; x5++) {
            if (x5 == 0) continue;
            int another_part = -a4 * pow3(x4) - a5 * pow3(x5);
            cnt += upper_bound(part, part + MAX_IDX, another_part) -         \
                   lower_bound(part, part + MAX_IDX, another_part);
        }
    }
    printf("%d\n", cnt);

    return 0;
}
