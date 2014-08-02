/*
 *  SRC: POJ 3881
 * PROB: Happy Telephones
 * ALGO: NULL
 * DATE: Aug 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;
using std::lower_bound;
using std::upper_bound;

int main()
{
    int n, m;
    vector<int> start, end;
    while (scanf("%d%d", &n, &m), n && m) {
        start.clear();
        end.clear();
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%*d%*d%d%d", &a, &b);
            b = a + b;
            start.push_back(a);
            end.push_back(b);
        }

        sort(start.begin(), start.end());
        sort(end.begin(), end.end());

        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            b = a + b;
            int i = start.end() - lower_bound(start.begin(), start.end(), b),
                j = upper_bound(end.begin(), end.end(), a) - end.begin();
            printf("%d\n", n - i - j);
        }
    }

    return 0;
}

