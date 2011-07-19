/*
 *  SRC: POJ 1328
 * PROB: Radar Installation
 * ALGO: Greedy
 * DATE: Jul 18, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;

const double pi = acos(-1);

int n, d;

struct Node {
    int x, y;

} isl[1000];

struct Interval {
    double a, b;

    bool operator < (const Interval& other) const
    {
        return a < other.a;
    }
} iv[1000];

int main()
{
    int T = 0;
LOOP:
    while (scanf("%d%d", &n, &d) != EOF) {
        if (!(n || d)) break;

        for (int i = 0; i < n; i++)
            scanf("%d%d", &isl[i].x, &isl[i].y);

        for (int i = 0; i < n; i++) {
            if (isl[i].y > d) {
                printf("Case %d: -1\n", ++T);
                goto LOOP;
            }
            iv[i].a = isl[i].x - sqrt(d * d - isl[i].y * isl[i].y);
            iv[i].b = isl[i].x + sqrt(d * d - isl[i].y * isl[i].y);
        }

        sort(iv, iv + n);
        
        int cnt = n;
        for (int i = 0; i < n - 1; i++) {
            if (iv[i].a <= iv[i + 1].a && iv[i + 1].a <= iv[i].b) {
                if (iv[i].b < iv[i + 1].b)
                    iv[i + 1].b = iv[i].b;
                cnt--;
            }
        }

        printf("Case %d: %d\n", ++T, cnt);
    } 

    return 0;
}
