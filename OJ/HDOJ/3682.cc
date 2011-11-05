/*
 *  SRC: HDOJ 3682
 * PROB: To Be an Dream Architect
 * ALGO: Math
 * DATE: Nov 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using std::vector;
using std::swap;
using std::pair;

typedef vector<int>::const_iterator vci;

struct Line {
    pair<char, int> a, b;

    void sort()
    {
        if (a.first > b.first) swap(a, b);
    }
};
Line l[1010];
vector<int> v[1010];
int map[1010][1010];
int xy[1010][1010],
    xz[1010][1010],
    yz[1010][1010];

inline bool intersect(const Line &l1, const Line &l2) 
{
    if (l1.a == l2.a && l1.b.first != l2.b.first) return true;
    if (l1.a == l2.b && l1.b.first != l2.a.first) return true;
    if (l1.b == l2.a && l1.a.first != l2.b.first) return true;
    if (l1.b == l2.b && l1.a.first != l2.a.first) return true;
    return false;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);

    for (int task = 1; task <= tasks; task++) {
        int n, m, cnt = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            char c;
            int  p;
            scanf(" %c%*c%d", &c, &p);
            l[cnt].a = pair<char, int>(c, p);
            scanf("%*c%c%*c%d", &c, &p);
            l[cnt].b = pair<char, int>(c, p);

            if (l[cnt].a.second > n || l[cnt].b.second > n) continue;
            l[cnt].sort();

            if (l[cnt].a.first == 'X' && l[cnt].b.first == 'Y') {
                if (xy[l[cnt].a.second][l[cnt].b.second] == task) continue;
                else xy[l[cnt].a.second][l[cnt].b.second] = task;
            }
            else if (l[cnt].a.first == 'X' && l[cnt].b.first == 'Z') {
                if (xz[l[cnt].a.second][l[cnt].b.second] == task) continue;
                else xz[l[cnt].a.second][l[cnt].b.second] = task;
            }
            else if (l[cnt].a.first == 'Y' && l[cnt].b.first == 'Z') {
                if (yz[l[cnt].a.second][l[cnt].b.second] == task) continue;
                else yz[l[cnt].a.second][l[cnt].b.second] = task;
            }

            v[cnt++].clear();
        }
        m = cnt;

        int ans = n * m;
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++)
                if (intersect(l[i], l[j])) {
                    v[i].push_back(j);
                    map[i][j] = map[j][i] = task;
                    ans--;
                }

        for (int i = 0; i < m; i++) {
            for (vci j = v[i].begin(); j != v[i].end(); j++)
                for (vci k = v[*j].begin(); k != v[*j].end(); k++)
                    if (map[i][*k] == task) ans++;
        }

        printf("%d\n", ans);
    }
    
    return 0;
}
