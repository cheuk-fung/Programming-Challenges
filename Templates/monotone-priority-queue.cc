/*
 *  SRC: POJ 1821
 * PROB: Fence
 * ALGO: DP + Monotone Priority Queue(decrease)
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int n, m;
int f[101][16001], que[16001];

struct Node {
    int l, p, s;

    bool operator<(const Node& other) const
    {
        return s < other.s;
    }
} worker[101];

inline int key(int i, int k)
{
    return f[i - 1][k] - k * worker[i].p;
}

/*
 * f[i][j] = {
 *              f[i - 1][j],
 *              f[i][j - 1],
 *              f[i - 1][k] + (j - k) * worker[i].p => (f[i - 1][k] - k * worker[i].p) + j * worker[i].p
 *           }
 */

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &worker[i].l, &worker[i].p, &worker[i].s);

    sort(worker + 1, worker + m + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < worker[i].s; j++) f[i][j] = f[i - 1][j];

        int head = 0, tail = 0;
        for (int k = max(worker[i].s - worker[i].l, 0); k < worker[i].s; k++) {
            while (head < tail && key(i, que[tail - 1]) <= key(i, k)) tail--;
            que[tail++] = k;
        }

        for (int j = worker[i].s, finish = min(worker[i].s + worker[i].l, n + 1); j < finish; j++) {
            while (head < tail && que[head] < j - worker[i].l) head++;
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            f[i][j] = max(f[i][j], key(i, que[head]) + j * worker[i].p);
        }

        for (int j = worker[i].s + worker[i].l; j <= n; j++)
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
    }

    printf("%d\n", f[m][n]);

    return 0;
}
