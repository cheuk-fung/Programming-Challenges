/*
 *  SRC: HDOJ 4022
 * PROB: Bombing
 * ALGO: NULL
 * DATE: Sep 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <map>
#include <set>

using std::multiset;
using std::map;

const int MAX_N = 100010;

map< int, multiset<int> > row, col;

int bomb(map< int, multiset<int> > &r, map< int, multiset<int> > &c, int d)
{
    int res = r[d].size();
    for (multiset<int>::const_iterator it = r[d].begin(); it != r[d].end(); it++)
        c[*it].erase(d);
    r[d].clear();
    return res;
}

int main()
{
    int n, m, x, y, c, d;
    while (scanf("%d%d", &n, &m), n || m) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            row[x].insert(y);
            col[y].insert(x);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &c, &d);
            printf("%d\n", c ? bomb(col, row, d) : bomb(row, col, d));
        }
        putchar(10);
        row.clear();
        col.clear();
    }
    
    return 0;
}
