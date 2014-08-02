/*
 *  SRC: ZOJ 3622
 * PROB: Magic Number
 * ALGO: NULL
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

int lol[] = {1, 2, 5, 25, 125};

int main()
{
    int m, n;
    while (~scanf("%d%d", &m, &n)) {
        int cnt = 0;
        for (int i = 0; i < 5; i++) {
            long long y = lol[i];
            while (y < m) y *= 10;
            while (y <= n) {
                cnt++;
                y *= 10;
            }
        }

        printf("%d\n", cnt);
    }

    return 0;
}
