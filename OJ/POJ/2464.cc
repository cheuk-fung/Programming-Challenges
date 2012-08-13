/*
 *  SRC: POJ 2464
 * PROB: Brownie Points II
 * ALGO: BIT
 * DATE: Aug 13, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 2000010;

class BIT {
    private:
        int c[MAXN];
        int lowbit(int x) { return x & -x; }

    public:
        void build() { memset(c, 0, sizeof c); }

        void update(int x, int v)
        {
            for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ;
        }

        int query(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }

} lbit, rbit;

pii pnt[MAXN];
int xall[MAXN], xcnt;
int yall[MAXN], ycnt;

pii calc(pii *first, pii *last)
{
    for (pii *it = first; it != last; it++) {
        rbit.update(it->second, -1);
    }

    pii r(-1, -1);
    for (pii *it = first; it != last; it++) {
        int stan = lbit.query(it->second - 1) + (rbit.query(MAXN - 1) - rbit.query(it->second));
        int ollie = lbit.query(MAXN - 1) - lbit.query(it->second) + rbit.query(it->second - 1);
        if (ollie > r.second) {
            r.first = stan;
            r.second = ollie;
        } else if (ollie == r.second) {
            r.first = min(r.first, stan);
        }
    }

    for (pii *it = first; it != last; it++) {
        lbit.update(it->second, 1);
    }

    return r;
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].first, &pnt[i].second);
            xall[i] = pnt[i].first;
            yall[i] = pnt[i].second;
        }
        sort(pnt, pnt + n);
        sort(xall, xall + n);
        sort(yall, yall + n);
        xcnt = unique(xall, xall + n) - xall;
        ycnt = unique(yall, yall + n) - yall;
        for (int i = 0; i < n; i++) {
            pnt[i].first = lower_bound(xall, xall + xcnt, pnt[i].first) - xall + 1;
            pnt[i].second = lower_bound(yall, yall + ycnt, pnt[i].second) - yall + 1;
        }
        pnt[n] = pii(-1, -1);

        lbit.build();
        rbit.build();
        for (int i = 0; i < n; i++) {
            rbit.update(pnt[i].second, 1);
        }

        int xans = 0;
        set<int> yans;
        pii *first = pnt, *last = pnt;
        for (int i = 1; i <= n; i++) {
            if (pnt[i].first == last->first) {
                last++;
            } else {
                pii r = calc(first, last + 1);
                if (r.first > xans) {
                    xans = r.first;
                    yans.clear();
                    yans.insert(r.second);
                } else if (r.first == xans) {
                    yans.insert(r.second);
                }

                first = last = pnt + i;
            }
        }

        printf("Stan: %d; Ollie:", xans);
        for (set<int>::iterator it = yans.begin(); it != yans.end(); it++) {
            printf(" %d", *it);
        }
        puts(";");
    }

    return 0;
}

