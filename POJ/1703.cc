/*
 *  SRC: POJ 1703
 * PROB: Find them, Catch them
 * ALGO: Disjoint Set
 * DATE: Jul 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 100010;

class Disjoint_Set
{
    public:
        int a[MAXN];

        void reset(int n)
        {
            for (int i = 0; i < n; i++) {
                a[i] = i;
            }
        }

        int find(int u)
        {
            if (a[u] == u) return u;
            int x = find(abs(a[u]));
            if ((long long)a[u] * x > 0) return a[u] = abs(x);
            else return a[u] = -abs(x);
        }

        void join(int u, int v)
        {
            int x = find(u);
            int y = find(v);
            if (abs(x) != abs(y)) {
                if ((long long)x * y > 0) a[abs(y)] = -abs(x);
                else a[abs(y)] = abs(x);
            }
        }
} ds;

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);
        ds.reset(n + 1);
        for (int i = 0; i < m; i++) {
            char c;
            int u, v;
            scanf(" %c%d%d", &c, &u, &v);
            if (c == 'D') ds.join(u, v);
            else {
                int x = ds.find(u);
                int y = ds.find(v);
                if (x == y) puts("In the same gang.");
                else if (x == -y) puts("In different gangs.");
                else puts("Not sure yet.");
            }
        }
    }

    return 0;
}

