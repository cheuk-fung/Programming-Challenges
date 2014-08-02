/*
 *  SRC: NKOJ 2172
 * PROB: Free Goodies
 * ALGO: DP
 * DATE: Aug 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;
using std::pair;
using std::make_pair;
using std::max;

int n;
pair<int, int> v[1001], f[1001];

int main()
{
    int jobs;
    char name[10];
    scanf("%d", &jobs);
    while (jobs--) {
        scanf("%d%s", &n, name);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &v[i].first, &v[i].second);
            v[i].first *= -1;
        }
        sort(v + 1, v + 1 + n);

        int offset = 0;
        if (name[0] == 'J') offset = 1;

        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++) {
            for (int j = (i + offset) / 2; j > 0; j--)
                f[j] = max(make_pair(f[j].first, f[j].second - v[i].first), \
                        make_pair(f[j - 1].first + v[i].second, f[j - 1].second));
            f[0].second -= v[i].first;
        }

        printf("%d %d\n", f[(n + offset) / 2].second, \
                f[(n + offset) / 2].first);
    }

    return 0;
}
