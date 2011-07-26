/*
 *  SRC: POJ 1468
 * PROB: Rectangles
 * ALGO: Computational Geometry
 * DATE: Jul 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

struct Rectangle {
    int x1, y1, x2, y2;
} rec[5000];

int n;

inline bool check(const Rectangle& a, const Rectangle& b)
{
    return a.x1 >= b.x1 && a.y1 >= b.y1 && a.x2 <= b.x2 && a.y2 <= b.y2;
}

int main()
{
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &rec[i].x1, &rec[i].x2, &rec[i].y1, &rec[i].y2);

        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && check(rec[i], rec[j])) {
                    cnt++;
                    break;
                }

        printf("%d\n", cnt);
    }

    return 0;
}
