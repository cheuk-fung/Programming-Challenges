/*
 *  SRC: HDOJ 4394
 * PROB: Digital Square
 * ALGO: DFS
 * DATE: Aug 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
long long ans;
long long ten[20];

void dfs(long long m, int depth)
{
    if (n % ten[depth] == n) {
        ans = min(m, ans);
        return ;
    }

    for (int i = 0; i <= 9; i++) {
        long long t = i * ten[depth] + m;
        if (t * t % ten[depth + 1] != n % ten[depth + 1]) continue;
        dfs(t, depth + 1);
    }
}

int main()
{
    ten[0] = 1;
    for (int i = 1; i < 15; i++) ten[i] = ten[i - 1] * 10;

    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d", &n);
        ans = LLINF;
        dfs(0, 0);
        if (ans != LLINF) {
            cout << ans;
        } else {
            cout << "None";
        }
        cout << endl;
    }

    return 0;
}

