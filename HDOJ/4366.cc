/*
 *  SRC: HDOJ 4366
 * PROB: Successor
 * ALGO: Segment tree
 * DATE: Aug 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 50010;

class Segment_tree {
    private:
        static int lep, rep;

        int loyalty[MAXN << 2];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void push_up(int idx)
        {
            loyalty[idx] = max(loyalty[LC(idx)], loyalty[RC(idx)]);
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(loyalty, 0xff, sizeof loyalty);
        }

        void update(int p, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                loyalty[idx] = v;
                return ;
            }

            int mid = (a + b) >> 1;
            if (p < mid) update(p, v, a, mid, LC(idx));
            else update(p, v, mid, b, RC(idx));
            push_up(idx);
        }

        int query(int c, int d, int a = lep, int b = rep, int idx = 1)
        {
            if (c <= a && b <= d) {
                return loyalty[idx];
            }

            int res = -1, mid = (a + b) >> 1;
            if (c < mid) res = max(res, query(c, d, a, mid, LC(idx)));
            if (d > mid) res = max(res, query(c, d, mid, b, RC(idx)));
            return res;
        }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Staff {
    int ability;
    int sn;

    bool operator<(const Staff &o) const { return ability == o.ability ? sn < o.sn : ability > o.ability; }
} man[MAXN];

vector<int> e[MAXN];
map<int, int> sn;
int loyalty[MAXN], ans[MAXN];
int dfn, ldfn[MAXN], rdfn[MAXN];

void dfs(int u)
{
    ldfn[u] = rdfn[u] = dfn++;
    for (int i = 0; i < (int)e[u].size(); i++) {
        dfs(e[u][i]);
        rdfn[u] = rdfn[e[u][i]];
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);
        sn.clear();
        for (int i = 0; i < n; i++) e[i].clear();

        sn[-1] = -1;
        for (int i = 1; i < n; i++) {
            int a;
            scanf("%d%d%d", &a, loyalty + i, &man[i].ability);
            man[i].sn = i;
            e[a].push_back(i);
            sn[loyalty[i]] = i;
        }
        sort(man + 1, man + n);

        dfn = 0;
        dfs(0);

        st.build(0, n);
        for (int i = 1; i < n; i++) {
            int id = man[i].sn;
            int r = st.query(ldfn[id], rdfn[id] + 1);
            ans[id] = sn[r];
            st.update(ldfn[id], loyalty[id]);
        }

        for (int i = 0; i < m; i++) {
            int q;
            scanf("%d", &q);
            printf("%d\n", ans[q]);
        }
    }

    return 0;
}

