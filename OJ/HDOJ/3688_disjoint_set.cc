/*
 *  SRC: HDOJ 3688
 * PROB: Searchlights
 * ALGO: Disjoint Set
 * DATE: Nov 16, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

const int MAX_N = 110;
const int MAX_M = 10010;
const int INF   = 0x3f3f3f3f;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) { }
};

struct DisjointSet {
    int *p;
    int size;

    void init(int _size)
    {
        size = _size;
        p = new int[size];
    }

    void reset(int _size)
    {
        size = _size;
        memset(p, 0xff, sizeof(int) * (size + 1));
    }

    int find(int u)
    {
        if (p[u] < 0) return u;
        return p[u] = find(p[u]);
    }

    void join(int u, int v)
    {
        int x = find(u),
            y = find(v);
        p[x] += p[y];
        p[y] = x;
    }

    int remove(int u)
    {
        int x = find(u),
            y = find(u - 1);
        join(x, y);

        int left  = find(0),
            right = find(size);
        if (left == right) return INF;
        if (x == left || x == right) return -p[x];
        return (-p[x] + 2) >> 1;
    }
};
DisjointSet row[MAX_N], col[MAX_M];

int n, m;
vector<Point> l[10010];

int main()
{
    for (int i = 0; i < MAX_N; i++) row[i].init(MAX_M);
    for (int j = 0; j < MAX_M; j++) col[j].init(MAX_N);

    while (scanf("%d%d", &n, &m), n && m) {
        for (int i = 0; i <= n; i++) row[i].reset(m);
        for (int j = 0; j <= m; j++) col[j].reset(n);
        for (int i = 0; i <= n + m; i++) l[i].clear();

        int max_h = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                int h;
                scanf("%d", &h);
                h = min(h, n + m);
                l[h].push_back(Point(i, j));

                max_h = max(max_h, h);
            }

        int gap = 0;
        for (int i = 0; i <= max_h; i++) {
            for (int j = 0; j < l[i].size(); j++) {
                gap = max(gap, row[l[i][j].x].remove(l[i][j].y));
                gap = max(gap, col[l[i][j].y].remove(l[i][j].x));
            }

            if (gap == INF) break;
            if (gap <= i + 1) {
                printf("%d\n", i + 1);
                goto FIND_ANSWER;
            }
        }
        puts("NO ANSWER!");

FIND_ANSWER: ;
    }

    return 0;
}
