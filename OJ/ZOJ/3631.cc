/*
 *  SRC: ZOJ 3631
 * PROB: Watashi's BG
 * ALGO: DFS
 * DATE: Jul 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;

const int MAXN = 50;
const int MAXM = 10000010;

int n, m;
int val[MAXN];
long long sum[MAXN];
int ans;

void search(int x, int now)
{
    if (now + sum[x] <= ans) return ;
    ans = max(ans, now);
    for (int i = x; i < n; i++) {
        if (now + val[i] <= m) {
            search(i + 1, now + val[i]);
        }
    }
}

int main()
{
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", val + i);
        }

        sort(val, val + n, greater<int>());
        ans = 0;
        sum[n - 1] = val[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            sum[i] = sum[i + 1] + val[i];
            if (sum[i] <= m) ans = sum[i];
        }
        search(0, 0);
        printf("%d\n", ans);
    }

    return 0;
}
