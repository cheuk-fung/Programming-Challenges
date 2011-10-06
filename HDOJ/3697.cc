/*
 *  SRC: HDOJ 3697
 * PROB: Selecting courses
 * ALGO: Gready
 * DATE: Oct 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;
using std::max;

int n;
bool vis[300];

struct Course {
    int l, r;

    void read() { scanf("%d%d", &l, &r); }

    bool operator < (const Course &other) const
    {
        if (r == other.r) return l < other.l;
        return r < other.r;
    }
} c[300];

int main()
{
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) c[i].read();
        sort(c, c + n);

        int ans = 0;
        for (int start = 0; start < 5; start++) {
            memset(vis, 0, sizeof(vis));

            int cnt = 0, last = 0;
            for (int time = start; time <= 1000; time += 5) {
                while (time >= c[last].r && last < n) last++;
                for (int i = last; i < n; i++) {
                    if (time >= c[i].l && !vis[i]) {
                        cnt++;
                        vis[i] = 1;
                        break;
                    }
                }
            }

            ans = max(ans, cnt);
        }

        printf("%d\n", ans);
    }

    return 0;
}
