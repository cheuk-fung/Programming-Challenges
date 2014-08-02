/*
 *  SRC: HDOJ 4312
 * PROB: Meeting point-2
 * ALGO: Chebyshev distance
 * DATE: Jul 26, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

struct Point {
    long long x, y;   // Manhatton coordinates (Rotate Chebyshev coordinates by 45 degree anticlockwise then multiply by sqrt(2))
    long long cx, cy; // Chebyshev coordinates
    long long xlsum, xrsum;
    long long ylsum, yrsum;
};
Point pnt[MAXN];
int n;
int xpos[MAXN], ypos[MAXN];

inline long long myabs(long long x) { return x > 0 ? x : -x; }
bool cmpx(int a, int b) { return pnt[a].x < pnt[b].x; }
bool cmpy(int a, int b) { return pnt[a].y < pnt[b].y; }

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int cx, cy;
            scanf("%d%d", &cx, &cy);
            pnt[i].cx = cx;
            pnt[i].cy = cy;
            pnt[i].x = cx + cy;
            pnt[i].y = cy - cx;
            xpos[i] = ypos[i] = i;
        }
        sort(xpos, xpos + n, cmpx);
        sort(ypos, ypos + n, cmpy);

        pnt[xpos[0]].xlsum = pnt[ypos[0]].ylsum = 0;
        for (int i = 1; i < n; i++) {
            pnt[xpos[i]].xlsum = pnt[xpos[i - 1]].xlsum + i * (pnt[xpos[i]].x - pnt[xpos[i - 1]].x);
            pnt[ypos[i]].ylsum = pnt[ypos[i - 1]].ylsum + i * (pnt[ypos[i]].y - pnt[ypos[i - 1]].y);
        }
        pnt[xpos[n - 1]].xrsum = pnt[ypos[n - 1]].yrsum = 0;
        for (int i = n - 2; i >= 0; i--) {
            pnt[xpos[i]].xrsum = pnt[xpos[i + 1]].xrsum + (n - i - 1) * (pnt[xpos[i + 1]].x - pnt[xpos[i]].x);
            pnt[ypos[i]].yrsum = pnt[ypos[i + 1]].yrsum + (n - i - 1) * (pnt[ypos[i + 1]].y - pnt[ypos[i]].y);
        }

        long long ans = LLINF;
        for (int i = 0; i < n; i++) {
            ans = min(ans, pnt[i].xlsum + pnt[i].xrsum + pnt[i].ylsum + pnt[i].yrsum);
        }

        cout << ans / 2 << endl;
    }

    return 0;
}

