/*
 *  SRC: POJ 1167
 * PROB: The Buses
 * ALGO: dfs
 * DATE: Aug 04, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

struct Node {
    int start, interval, cnt;

    bool operator<(const Node& other) const
    {
        return cnt > other.cnt;
    }
} path[1000];

int n, tot, bus[60];
int ans = 17;

bool check(int start, int interval)
{
    for (int t = start; t < 60; t += interval)
        if (!bus[t]) return false;
    return true;
}

void dfs(int curr, int depth)
{
    if (depth >= ans) return ;

    if (n == 0) {
        ans = depth;
        return ;
    }

    for (int index = curr; index < tot; index++) {
        if (depth + n / path[index].cnt >= ans) return ;
        if (check(path[index].start, path[index].interval)) {
            int time = path[index].start, interval = path[index].interval;
            for (int t = time; t < 60; t += interval) {
                bus[t]--;
                n--;
            }
            dfs(index, depth + 1);
            for (int t = time; t < 60; t += interval) {
                bus[t]++;
                n++;
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        bus[t]++;
    }

    for (int i = 0; i < 30; i++) {
        if (!bus[i]) continue;
        for (int j = i + 1; i + j < 60; j++)
            if (check(i, j)) {
                path[tot].start = i;
                path[tot].interval = j;
                path[tot].cnt = (59 - i) / j + 1;
                tot++;
            }
    }

    sort(path, path + tot);
    dfs(0, 0);
    printf("%d\n", ans);

    return 0;
}
