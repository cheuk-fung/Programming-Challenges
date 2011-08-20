/*
 *  SRC: POJ 1011
 * PROB: Sticks
 * ALGO: DFS
 * DATE: Aug 18, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using std::sort;
using std::greater;

int n, stick[65];
bool used[65];

bool dfs(int depth, int left, int target, int pos)
{
    if (depth == n) {
        if (!left) return true;
        return false;
    }

    if (!left) {
        left = target;
        pos = 0;
    }
    for (int i = pos; i < n; i++) {
        if (stick[i] > left) continue;
        if (!used[i]) {
            used[i] = true;
            if (dfs(depth + 1, left - stick[i], target, i + 1)) return true;
            used[i] = false;
            if (stick[i] == left || left == target) return false;
            while (i + 1 < n && stick[i + 1] == stick[i]) i++;
        }
    }

    return false;
}

int main()
{
    while (scanf("%d", &n), n) {

        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", stick + i);
            sum += stick[i];
        }

        sort(stick, stick + n, greater<int>());

        for (int i = n; i > 0; i--)
            if (sum % i == 0 && sum / i >= stick[0]) {
                memset(used, 0, sizeof(used));
                if (dfs(0, sum / i, sum / i, 0)) {
                    printf("%d\n", sum / i);
                    break;
                }
            }
    }

    return 0;
}
