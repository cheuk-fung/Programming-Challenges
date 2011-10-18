/*
 *  SRC: POJ 2352
 * PROB: Stars
 * ALGO: BIT
 * DATE: Jul 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <algorithm>

using std::sort;

class BIT
{
    private:
        const static int bound = 320010; // change it to adapt to the problem
        int c[bound]; 
        int bitMask;

        // x must *not* be *zero*
        int lowbit(int x)
        {
            return x & -x;
        }

        void getBitMask()
        {
            int res = 0, x = bound;
            while (x) {
                x >>= 1;
                res++;
            }

            bitMask = 1 << (res - 1);
        }

    public:
        void update(int x, int val)
        {
            for (int i = x; i <= bound; i += lowbit(i))
                c[i] += val;
        }

        int sum(int x)
        {
            int res = 0;
            for (int i = x; i > 0; i -= lowbit(i))
                res += c[i];
            return res;
        }

        // getBitMask() first
        int find(int tot)
        {
            int res = 0, cnt = 0, bM = bitMask;
            while (bM != 0) {
                if (res + bM < bound && cnt + c[res + bM] < tot) { // find the left one
             // if (res + bM <=bound && cnt + c[res + bM] <=tot)   // find the right one
                    res += bM;
                    cnt += c[res];
                }
                bM >>= 1;
            }

            return res + 1; // left
         // return res;     // right
        }
};
BIT bit;

struct Point {
    int x, y;

    bool operator < (const Point& other) const
    {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
} star[15010];

int n;
int level[15010];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d%d", &star[i].x, &star[i].y);

    sort(star, star + n);

    for (int i = 0; i < n; i++) {
        bit.update(star[i].y + 1, 1);
        level[bit.sum(star[i].y + 1) - 1]++;
    }


    for (int i = 0; i < n; i++)
        printf("%d\n", level[i]);

    return 0;
}
