/*
 *  SRC: HDOJ 3884
 * PROB: Hinanai Tenshi’s peach garden
 * ALGO: NULL
 * DATE: Jun 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 10010;

struct Point {
    int x, p;
} peach[MAXN];

int main()
{
    int n;
    long long k;
    while (cin >> n >> k) {
        map<int, int> buf;
        for (int i = 0; i < n; i++) {
            int x, p;
            scanf("%d%d", &x, &p);
            buf[x] += p;
        }

        n = 0;
        for (map<int, int>::const_iterator it = buf.begin(); it != buf.end(); it++) {
            peach[n++] = (Point){it->first, it->second};
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int l = i - 1, r = i + 1;
            int cnt = peach[i].p;
            long long kk = k;
            while (true) {
                int m;
                if (l < 0) m = r++;
                else if (r >= n) m = l--;
                else m = abs(peach[l].x - peach[i].x) < abs(peach[r].x - peach[i].x) ? l-- : r++;
                if (m < 0 || m >= n) break;

                int delta = 0;
                long long dist = abs(peach[m].x - peach[i].x);
                if (dist * peach[m].p < kk) {
                    delta = peach[m].p;
                    kk -= dist * peach[m].p;
                } else {
                    delta = kk / dist;
                    kk -= dist * delta;
                }
                if (!delta) break;
                cnt += delta;
            }
            ans = max(ans, cnt);
        }

        printf("%d\n", ans);
    }

    return 0;
}
