/*
 *  SRC: POJ 3245
 * PROB: Sequence Partitioning
 * ALGO: Monotone Priority Queue
 * DATE: Aug 24, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstdlib>

const int MAXN = 50010;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

int n;
long long limit;
long long a[MAXN], b[MAXN], na[MAXN], nb[MAXN], f[MAXN];
long long amx[MAXN];
long long sum[MAXN];
int que[MAXN];

template<typename T> inline T MAX(T a, T b) { return a > b ? a : b; }
template<typename T> inline T MIN(T a, T b) { return a < b ? a : b; }

class Treap {
    private:
        struct Tnode {
            long long key;
            int fix, cnt;
            Tnode *l, *r;
        } buf[MAXN];
        Tnode *root, *buftail;

        Tnode *left_rotate(Tnode *x)
        {
            Tnode *y = x->r;
            x->r = y->l;
            y->l = x;
            return y;
        }

        Tnode *right_rotate(Tnode *x)
        {
            Tnode *y = x->l;
            x->l = y->r;
            y->r = x;
            return y;
        }

        Tnode *insert(Tnode *x, long long key)
        {
            if (!x) {
                x = buftail++;
                x->key = key;
                x->fix = rand() * rand();
                x->cnt = 1;
                x->l = x->r = 0;
                return x;
            }

            if (key < x->key) {
                x->l = insert(x->l, key);
                if (x->l->fix > x->fix) x = right_rotate(x);
            } else if (key > x->key) {
                x->r = insert(x->r, key);
                if (x->r->fix > x->fix) x = left_rotate(x);
            } else {
                x->cnt++;
            }
            return x;
        }

        Tnode *erase(Tnode *x, long long key)
        {
            if (!x) return 0;

            if (key < x->key) x->l = erase(x->l, key);
            else if (key > x->key) x->r = erase(x->r, key);
            else {
                if (x->cnt > 1) {
                    x->cnt--;
                    return x;
                }

                if (!x->l && !x->r) return 0;
                if (!x->l) x = left_rotate(x);
                else if (!x->r) x = right_rotate(x);
                else if (x->l->fix < x->r->fix) x = left_rotate(x);
                else x = right_rotate(x);
                x = erase(x, key);
            }

            return x;
        }

    public:
        void build() { root = 0; buftail = buf; }
        void insert(long long key) { root = insert(root, key); }
        void erase(long long key) { root = erase(root, key); }

        long long min_element() const
        {
            if (!root) return LLINF;

            Tnode *x = root;
            while (x->l) x = x->l;
            return x->key;
        }
} priority;

bool check(long long m)
{
    priority.build();

    int head = 0, tail = 0;
    int lower = 1;
    for (int i = 1; i <= n; i++) {
        while (sum[i] - sum[lower - 1] > m) lower++;

        while (head < tail && que[head] < lower) {
            head++;
            if (head < tail) priority.erase(f[que[head - 1]] + na[que[head]]);
        }
        while (head < tail && na[que[tail - 1]] <= na[i]) {
            tail--;
            if (head < tail) priority.erase(f[que[tail - 1]] + na[que[tail]]);
        }
        if (head < tail) {
            priority.insert(f[que[tail - 1]] + na[i]);
        }
        que[tail++] = i;

        f[i] = MIN(f[lower - 1] + na[que[head]], priority.min_element());
    }

    return f[n] <= limit;
}

int main()
{
    scanf("%d%lld", &n, &limit);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", a + i, b + i);
    }
    for (int i = n; i > 0; i--) {
        amx[i] = MAX(amx[i + 1], a[i]);
    }

    int gid = 1;
    for (int i = 1; i <= n; gid++) {
        long long bmn = b[i];
        na[gid] = a[i];
        nb[gid] = b[i];
        for (i++; bmn <= amx[i]; i++) {
            na[gid] = MAX(na[gid], a[i]);
            nb[gid] += b[i];
            bmn = MIN(bmn, b[i]);
        }
    }
    n = gid - 1;

    long long l = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + nb[i];
        l = MAX(l, nb[i]);
    }

    long long r = LLINF;
    while (l < r) {
        long long mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%lld\n", l);

    return 0;
}

