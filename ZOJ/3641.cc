/*
 *  SRC: ZOJ 3641
 * PROB: Information Sharing
 * ALGO: Disjoint set
 * DATE: Aug 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int MAXN = 100010;

map<string, int> name;
set<int> info[MAXN];

class Disjoint_set {
    private:
        int a[MAXN];

    public:
        void build() { memset(a, 0xff, sizeof a); }

        int find(int u)
        {
            int r = u;
            while (a[r] >= 0) r = a[r];
            while (a[u] >= 0) {
                int v = a[u];
                a[u] = r;
                u = v;
            }
            return r;
        }

        void join(int u, int v)
        {
            int x = find(u), y = find(v);
            if (x != y) {
                if (info[x].size() < info[y].size()) {
                    swap(x, y);
                }
                a[x] += a[y];
                a[y] = x;
                for (set<int>::iterator it = info[y].begin(); it != info[y].end(); it++) {
                    info[x].insert(*it);
                }
            }
        }
} ds;

char strbuf[20];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ds.build();
        name.clear();
        for (int i = 0; i < n; i++) info[i].clear();

        int idx = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);

            if (strbuf[0] == 'a') {
                scanf("%s", strbuf);
                if (!name.count(strbuf)) name[strbuf] = idx++;
                int m;
                scanf("%d", &m);
                for (int j = 0; j < m; j++) {
                    int a;
                    scanf("%d", &a);
                    int idx1 = name[strbuf];
                    info[idx1].insert(a);
                }
            } else if (strbuf[0] == 's') {
                scanf("%s", strbuf);
                if (!name.count(strbuf)) name[strbuf] = idx++;
                int idx1 = name[strbuf];
                scanf("%s", strbuf);
                if (!name.count(strbuf)) name[strbuf] = idx++;
                int idx2 = name[strbuf];
                ds.join(idx1, idx2);
            } else {
                scanf("%s", strbuf);
                if (!name.count(strbuf)) name[strbuf] = idx++;
                int idx1 = name[strbuf];
                printf("%d\n", info[ds.find(idx1)].size());
            }
        }
    }

    return 0;
}

