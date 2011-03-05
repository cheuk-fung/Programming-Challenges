/*
 *  SRC: POJ
 * TASK: Gangsters
 * ALGO: DP
 * DATE: Dec. 12, 2010
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Gangster {
    int t, p, s;
};

bool cmp(Gangster a, Gangster b)
{
    if (a.t < b.t) return true;
    if (a.t > b.t) return false;
    return a.s < b.s;
}

inline int MAX(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int n, k, t;
    scanf("%d %d %d", &n, &k, &t);

    Gangster g[n];
    for (int i = 0; i < n; i++) scanf("%d", &g[i].t);
    for (int i = 0; i < n; i++) scanf("%d", &g[i].p);
    for (int i = 0; i < n; i++) scanf("%d", &g[i].s);

    sort(g, g + n, cmp);

    static int f[2][110], pg, ans;
    while (g[pg].t == 0 && g[pg].s == 0) f[0][0] += g[pg++].p;
    for (int i = 1; i < t + 1; i++)
	for (int j = 0; j < k + 1 && j < i + 1; j++) {
	    f[i % 2][j] = 0;
	    while (i > g[pg].t) pg++;
	    while (i == g[pg].t && j == g[pg].s) f[i % 2][j] += g[pg++].p;
	    int max = f[(i - 1) % 2][j];
	    if (j > 0) max = MAX(max, f[(i - 1) % 2][j - 1]);
	    if (j < k && j < i) max = MAX(max, f[(i - 1) % 2][j + 1]);
	    f[i % 2][j] += max;
	    ans = MAX(ans, f[i % 2][j]);
	}

    printf("%d\n", ans);

    return 0;
}

