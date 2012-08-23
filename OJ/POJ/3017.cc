/*
 *  SRC: POJ 3017
 * PROB: Cut the Sequence
 * ALGO: DP
 * DATE: Aug 23, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXN = 100010;

inline long long MIN(long long x, long long y) { return x < y ? x : y; }

class Treap {
    private:
        struct Tnode {
            long long key;
            int fix;
            int cnt;

            Tnode *l, *r;
        };
        Tnode buf[MAXN];
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

        Tnode *erase(Tnode *x, int key)
        {
            if (!x) return 0;
            if (key < x->key) x->l = erase(x->l, key);
            else if (key > x->key) x->r = erase(x->r, key);
            else {
                if (x->cnt > 1) {
                    x->cnt--;
                    return x;
                }

                if (!x->l && !x->r) {
                    return 0;
                }

                if (!x->l) x = left_rotate(x);
                else if (!x->r) x = right_rotate(x);
                else if (x->l->fix < x->r->fix) x = right_rotate(x);
                else x = left_rotate(x);
                x = erase(x, key);
            }

            return x;
        }

    public:
        Treap() : root(0), buftail(buf) { }
        void insert(long long key) { root = insert(root, key); }
        void erase(long long key) { root = erase(root, key); }
        long long min_element()
        {
            Tnode *x = root;
            while (x->l) x = x->l;
            return x->key;
        }
};

Treap priority;
long long a[MAXN], sum[MAXN], que[MAXN];
long long f[MAXN];

int getlower(int x, long long m)
{
    int l = 1, r = x;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (sum[x] - sum[mid - 1] <= m) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    // srand(time(0));

    int n;
    long long m;
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
        if (a[i] > m) {
            puts("-1");
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }

    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
        int lower = getlower(i, m);
        while (head < tail && a[que[tail - 1]] <= a[i]) {
            tail--;
            if (head < tail) priority.erase(f[que[tail - 1]] + a[que[tail]]);
        }
        while (head < tail && que[head] < lower)
        {
            priority.erase(f[que[head]] + a[que[head + 1]]);
            head++;
        }
        if (head == tail) {
            f[i] = f[lower - 1] + a[i];
        } else {
            priority.insert(f[que[tail - 1]] + a[i]);
            f[i] = MIN(priority.min_element(), f[lower - 1] + a[que[head]]);
        }
        que[tail++] = i;
    }

    printf("%lld\n", f[n]);

    return 0;
}

