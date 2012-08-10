/*
 *  SRC: HDOJ 4358
 * PROB: Boring counting
 * ALGO: BIT
 * DATE: Aug 10, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 10;

class BIT {
    private:
        int c[MAXN];
        int lowbit(int x) { return x & -x; }

    public:
        void clear() { memset(c, 0, sizeof c); }

        void update(int x, int v)
        {
            for ( ; x < MAXN; c[x] += v, x += lowbit(x)) ;
        }

        int sum(int x)
        {
            int res = 0;
            for ( ; x; res += c[x], x -= lowbit(x)) ;
            return res;
        }
} bit;

struct Query {
    int l, r, id;
    bool operator<(const Query &o) const { return r < o.r; }
} que[MAXN];

int n, k, dfn;
map<int, int> discrete;
vector<int> e[MAXN], prev[MAXN];
int w[MAXN], ans[MAXN], indfn[MAXN], outdfn[MAXN], seq[MAXN];

void dfs(int u, int parent)
{
    seq[dfn] = u;
    indfn[u] = outdfn[u] = dfn++;
    for (int i = 0; i < (int)e[u].size(); i++) {
        int v = e[u][i];
        if (v != parent) {
            dfs(v, u);
            outdfn[u] = outdfn[v];
        }
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        printf("Case #%d:\n", task);
        scanf("%d%d", &n, &k);

        dfn = 1;
        bit.clear();
        discrete.clear();
        for (int i = 1; i <= n; i++) {
            e[i].clear();
            prev[i].clear();
            prev[i].push_back(0);
        }

        int idx = 1;
        for (int i = 1; i <= n; i++) {
            scanf("%d", w + i);
            if (!discrete.count(w[i])) discrete[w[i]] = idx++;
            w[i] = discrete[w[i]];
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }

        dfs(1, 0);

        int q;
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int u;
            scanf("%d", &u);
            que[i].l = indfn[u];
            que[i].r = outdfn[u];
            que[i].id = i;
        }
        sort(que, que + q);

        for (int i = 1, j = 0; i <= n; i++) {
            int u = seq[i];
            prev[w[u]].push_back(i);
            if ((int)prev[w[u]].size() > k) {
                int now = prev[w[u]].size() - 1;
                if (now - k - 1 >= 0) {
                    bit.update(prev[w[u]][now - k - 1] + 1, -1);
                    bit.update(prev[w[u]][now - k] + 1, 1);
                }
                bit.update(prev[w[u]][now - k] + 1, 1);
                bit.update(prev[w[u]][now - k + 1] + 1, -1);
            }
            while (j < q && que[j].r == i) {
                ans[que[j].id] = bit.sum(que[j].l);
                j++;
            }
            if (j == q) break;
        }
        for (int i = 0; i < q; i++) {
            printf("%d\n", ans[i]);
        }

        if (task != tasks) putchar(10);
    }


    return 0;
}

