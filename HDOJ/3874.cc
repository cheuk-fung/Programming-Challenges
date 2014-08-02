/*
 *  SRC: HDOJ 3874
 * PROB: Necklace
 * ALGO: BIT
 * DATE: May 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 51000;

class BIT {
    private:
        long long c[MAXN];

        int lowbit(int x) { return x & -x; }
    public:
        void reset()
        {
            memset(c, 0, sizeof(c));
        }

        void update(int x, int v)
        {
            for ( ; x < MAXN; x += lowbit(x)) {
                c[x] += v;
            }
        }

        long long sum(int x)
        {
            long long res = 0;
            for ( ; x; x -= lowbit(x)) {
                res += c[x];
            }
            return res;
        }
};

struct Query {
    int l, r, id;
    long long ans;
};
bool cmp_r(const Query &x, const Query &y) { return x.r < y.r; }
bool cmp_id(const Query &x, const Query &y) { return x.id < y.id; }

BIT bit;
Query q[200010];
int ball[MAXN], last[1000010];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        bit.reset();
        memset(last, 0xff, sizeof(last));

        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", ball + i);
        }

        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].id = i;
        }
        sort(q, q + m, cmp_r);

        int now = 1;
        for (int i = 0; i < m; i++) {
            for ( ; now <= q[i].r; now++) {
                if (last[ball[now]] > -1) {
                    bit.update(last[ball[now]], -ball[now]);
                }
                bit.update(now, ball[now]);
                last[ball[now]] = now;
            }
            q[i].ans = bit.sum(q[i].r) - bit.sum(q[i].l - 1);
        }

        sort(q, q + m, cmp_id);
        for (int i = 0; i < m; i++) {
            printf("%I64d\n", q[i].ans);
        }
    }

    return 0;
}

