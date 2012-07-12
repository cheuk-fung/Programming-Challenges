/*
 *  SRC: POJ 2492
 * PROB: A Bug's Life
 * ALGO: Disjoint Set
 * DATE: Jul 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>

const int MAXN = 2222;

class Disjoint_Set {
    public:
        int a[MAXN];

        void reset(int n)
        {
            for (int i = 0; i < n; i++) a[i] = i;
        }

        int find(int u)
        {
            if (a[u] == u) return u;
            int x = find(abs(a[u]));
            if ((long long)a[u] * x > 0) return a[u] = abs(x);
            else return a[u] = -abs(x);
        }

        bool join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (abs(x) != abs(y)) {
                if ((long long)x * y > 0) a[abs(y)] = -abs(x);
                else a[abs(y)] = abs(x);
            } else if (x == y) {
                return false;
            }
            return true;
        }
} ds;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Scenario #%d:\n", task);

        int n, m;
        scanf("%d%d", &n, &m);
        ds.reset(n + 1);

        bool flag = true;
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);

            if (flag && !ds.join(u, v)) {
                flag = false;
                puts("Suspicious bugs found!");
            }
        }
        if (flag) puts("No suspicious bugs found!");
        putchar(10);
    }

    return 0;
}

