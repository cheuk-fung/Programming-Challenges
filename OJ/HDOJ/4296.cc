/*
 *  SRC: HDOJ 4296
 * PROB: Buildings
 * ALGO: Greedy
 * DATE: Sep 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

struct Floor {
    int w, s;

    bool operator<(const Floor &o) const { return w + s == o.w +o.s ? s > o.s : w + s < o.w + o.s; }
} fl[MAXN];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &fl[i].w, &fl[i].s);
        }
        sort(fl, fl + n);

        long long ans = 0xc0c0c0c0c0c0c0c0ll;
        long long now = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, now - fl[i].s);
            now += fl[i].w;
        }
        printf("%I64d\n", ans);
    }

    return 0;
}

