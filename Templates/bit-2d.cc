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
        void update(int x, int y, int v)
        {
            for ( ; x <= bound_x; x += lowbit(x))
                for (int ty = y; ty <= bound_y; ty += lowbit(ty))
                    c[x][ty] += v;
        }

        int sum(int x, int y)
        {
            int res = 0;
            for ( ; x; x -= lowbit(x))
                for (int ty = y; ty; ty -= lowbit(ty))
                    res += c[x][ty];
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
