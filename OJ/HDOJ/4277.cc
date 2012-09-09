/*
 *  SRC: HDOJ 4277
 * PROB: USACO ORZ
 * ALGO: DFS
 * DATE: Sep 08, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const long long MM = 150000;
const long long MMMM = MM * MM;
const int MOD = 1000007;

int n, ans, all;
int tri[3], len[20];

void dfs(int depth, int a, int b, int c, set<long long> &vis)
{
    tri[0] = a; tri[1] = b; tri[2] = c;
    sort(tri, tri + 3);
    long long now = (tri[0] * MMMM + tri[1] * MM + tri[2]) * 15 + depth;
    if (vis.count(now)) return ;
    vis.insert(now);

    int mx = max(a, max(b, c));
    if (all - mx <= mx) return ;

    if (depth == n) {
        if (a && b && c && a + b > c && abs(a - b) < c) {
            ans++;
        }
        return ;
    }
    dfs(depth + 1, a + len[depth], b, c, vis);
    dfs(depth + 1, a, b + len[depth], c, vis);
    dfs(depth + 1, a, b, c + len[depth], vis);
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d", &n);
        all = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", len + i);
            all += len[i];
        }
        set<long long> vis;
        ans = 0;
        dfs(0, 0, 0, 0, vis);
        printf("%d\n", ans);
    }

    return 0;
}

