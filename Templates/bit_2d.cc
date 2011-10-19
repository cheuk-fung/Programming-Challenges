/*
 *  SRC: POJ 1195
 * PROB: Mobile phones
 * ALGO: 2D BIT(Binary Indexed Tree)
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

class BIT_2D {
    private:
        const static int bound_x = 1024, bound_y = 1024;
        int c[bound_x + 1][bound_y + 1];

        // x must *not* be *zero*
        int lowbit(int x) { return x & -x; }

    public:
        void update(int x, int y, int val)
        {
            while (x <= bound_x) {
                int ty = y;
                while (ty <= bound_y) {
                    c[x][ty] += val;
                    ty += lowbit(ty);
                }
                x += lowbit(x);
            }
        }

        int sum(int x, int y)
        {
            int res = 0;
            while (x > 0) {
                int ty = y;
                while (ty > 0) {
                    res += c[x][ty];
                    ty -= lowbit(ty);
                }
                x -= lowbit(x);
            }
            return res;
        }
};
BIT_2D bit;

int n;

int main()
{
    int ins;
    scanf("%d", &ins);
    scanf("%d", &n);

    while (scanf("%d", &ins) != EOF && ins != 3) {
        if (ins == 1) {
            int x, y, a;
            scanf("%d%d%d", &x, &y, &a);
            bit.update(x + 1, y + 1, a);
        }
        else {
            int l, b, r, t;
            scanf("%d%d%d%d", &l, &b, &r, &t);
            printf("%d\n", bit.sum(r + 1, t + 1) - bit.sum(l, t + 1) - \
                           bit.sum(r + 1, b) + bit.sum(l, b));
        }
    }

    return 0;
}
