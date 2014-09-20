#include <iostream>

using namespace std;

const int BOUND = 100010;

long long a[BOUND];

struct Operation {
    int l, r, d;
} opr[BOUND];

class BIT {
    private:
        long long c[BOUND];
        int lowbit(int x) { return x & -x; }

    public:
        void update(int x, long long v)
        {
            for ( ; x < BOUND; x += lowbit(x))
                c[x] += v;
        }

        long long sum(int x)
        {
            long long res = 0;
            for ( ; x > 0; x -= lowbit(x))
                res += c[x];
            return res;
        }
};
BIT bit_a, bit_opr;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> opr[i].l >> opr[i].r >> opr[i].d;
    }
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        bit_opr.update(x, 1);
        bit_opr.update(y + 1, -1);
    }

    for (int i = 1; i <= m; i++) {
        long long cnt = bit_opr.sum(i);
        bit_a.update(opr[i].l, opr[i].d * cnt);
        bit_a.update(opr[i].r + 1, -opr[i].d * cnt);
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] + bit_a.sum(i) << endl;
    }

    return 0;
}
