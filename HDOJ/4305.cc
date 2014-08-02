/*
 *  SRC: HDOJ 4305
 * PROB: Lightning
 * ALGO: Marix tree theorem
 * DATE: Jul 22, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 333;
const int MOD = 10007;

struct Point {
    int x, y;
};
Point pnt[MAXN];

int A[MAXN][MAXN];

int modnum(int x) { return (x % MOD + MOD) % MOD; }

int moddiv(int a, int b)
{
    int r = 1;
    for (int power = MOD - 2; power; power >>= 1) {
        if (power & 1) r = r * b % MOD;
        b = b * b % MOD;
    }

    return a * r % MOD;
}

int det(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (A[i][j] % MOD + MOD) % MOD;
        }
    }

    int res = 1;
    int sign = 1;
    int multiple = 1;
    for (int xc = 0; xc < n; xc++) {
        int row = xc;
        if (!A[row][xc]) {
            for (int i = row + 1; i < n; i++) {
                if (A[i][xc]) {
                    row = i;
                    break;
                }
            }
        }
        if (!A[row][xc]) return 0;

        if (row != xc) {
            swap_ranges(A[xc], A[xc] + n, A[row]);
        }
        if ((row - xc) & 1) sign *= -1;

        for (int i = xc + 1; i < n; i++) {
            if (!A[i][xc]) continue;

            for (int j = xc + 1; j < n; j++) {
                A[i][j] = modnum(A[i][j] * A[xc][xc] - A[xc][j] * A[i][xc]);
            }
            A[i][xc] = 0;

            multiple = multiple * A[xc][xc] % MOD;
        }

        res = res * A[xc][xc] % MOD;
    }

    return moddiv(modnum(sign * res), multiple);
}

inline int sqr(int x) { return x * x; }

inline int cross(const Point &a, const Point &b, const Point &o)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline bool in_seg(const Point &a, const Point &b, const Point &c)
{
    if (cross(b, c, a)) return false;
    if (c.x < min(a.x, b.x) || c.x > max(a.x, b.x)) return false;
    if (c.y < min(a.y, b.y) || c.y > max(a.y, b.y)) return false;
    return true;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(A, 0, sizeof A);

        int n, r;
        scanf("%d%d", &n, &r);
        r *= r;
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].x, &pnt[i].y);
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (sqr(pnt[i].x - pnt[j].x) + sqr(pnt[i].y - pnt[j].y) <= r) {
                    bool flag = true;
                    for (int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        if (in_seg(pnt[i], pnt[j], pnt[k])) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        A[i][j] = A[j][i] = -1;
                        A[i][i]++;
                        A[j][j]++;
                    }
                }
            }
        }

        int ans = det(n - 1);
        printf("%d\n", ans ? ans : -1);
    }

    return 0;
}

