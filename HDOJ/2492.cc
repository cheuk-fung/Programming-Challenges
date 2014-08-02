/*
 *  SRC: HDOJ 2492
 * PROB: Ping pong
 * ALGO: BIT
 * DATE: Nov 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;

class BIT {
    private:
        const static int bound = 100010;
        int c[bound + 1];
        
        int lowbit(int x) { return x & -x; }

    public:
        void reset()
        {
            memset(c, 0, sizeof(c));
        }

        void update(int x, int val)
        {
            while (x <= bound) {
                c[x] += val;
                x += lowbit(x);
            }
        }

        int sum(int x)
        {
            int res = 0;
            while (x > 0) {
                res += c[x];
                x -= lowbit(x);
            }
            return res;
        }
};
BIT bit_l, bit_r;

int a[20010];
int l_ls[20010], l_gr[20010], r_ls[20010], r_gr[20010];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        bit_l.reset();
        bit_r.reset();

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", a + i);

        for (int i = 0; i < n; i++) {
            bit_l.update(a[i], 1);
            l_ls[i] = bit_l.sum(a[i]) - 1;
            l_gr[i] = i - l_ls[i];
        }

        for (int i = n - 1; i >= 0; i--) {
            bit_r.update(a[i], 1);
            r_ls[i] = bit_r.sum(a[i]) - 1;
            r_gr[i] = n - 1 - i - r_ls[i];
        }

        long long res = 0;
        for (int i = 0; i < n; i++)
            res += (long long)l_ls[i] * r_gr[i] + (long long)l_gr[i] * r_ls[i];

        printf("%I64d\n", res);
    }
}
