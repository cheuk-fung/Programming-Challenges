/*
 *  SRC: POJ 2761
 * PROB: Feed the dogs
 * ALGO: Splay
 * DATE: Sep 08, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;
using std::sort;

const int MAXN = 100010;

class Splay {
    private:
        const static int BUF_SIZE = MAXN;
        int tree_size;

        struct Tnode {
            int key;
            int size, cnt;
            Tnode *l;
            Tnode *r;
        };

        Tnode buf[BUF_SIZE];
        Tnode *root;
        Tnode *buf_tail;

        Tnode *get_max(Tnode *x) const
        {
            while (x->r) x = x->r;
            return x;
        }

        Tnode *get_min(Tnode *x) const
        {
            while (x->l) x = x->l;
            return x;
        }

        void update_size(Tnode *x)
        {
            x->size = x->cnt;
            if (x->l) x->size += x->l->size;
            if (x->r) x->size += x->r->size;
        }

        void update_larger_size(Tnode *x, const Tnode *end)
        {
            if (x == end) return ;
            update_larger_size(x->l, end);
            update_size(x);
        }

        void update_smaller_size(Tnode *x, const Tnode *end)
        {
            if (x == end) return ;
            update_smaller_size(x->r, end);
            update_size(x);
        }

        Tnode *left_rotate(Tnode *x)
        {
            Tnode *y = x->r;
            x->r = y->l;
            y->l = x;
            update_size(x);
            return y;
        }

        Tnode *right_rotate(Tnode *x)
        {
            Tnode *y = x->l;
            x->l = y->r;
            y->r = x;
            update_size(x);
            return y;
        }

        Tnode *splay(Tnode *x, int key)
        {
            if (!x) return x;

            Tnode *y = new Tnode;
            y->l = y->r = 0;
            Tnode *larger = y;
            Tnode *smaller = y;

            while (key != x->key) {
                if (key < x->key) {
                    if (x->l && key < x->l->key) x = right_rotate(x);
                    if (!x->l) break;
                    larger->l = x;
                    larger = x;
                    x = x->l;
                } else {  // key > x->key
                    if (x->r && key > x->r->key) x = left_rotate(x);
                    if (!x->r) break;
                    smaller->r = x;
                    smaller = x;
                    x = x->r;
                }
            }

            larger->l = x->r;
            smaller->r = x->l;
            update_larger_size(y->l, larger->l);
            update_smaller_size(y->r, smaller->r);

            x->l = y->r;
            x->r = y->l;
            update_size(x);

            delete y;

            return x;
        }

        Tnode *_insert(Tnode *x, int key)
        {
            if (x) {
                x = splay(x, key);
                if (key == x->key) {
                    x->size++;
                    x->cnt++;
                    return x;
                }
            }

            tree_size++;
            Tnode *y = buf_tail++;
            y->key = key;
            y->size = y->cnt = 1;
            y->l = y->r = 0;

            if (!x) return y;

            if (key < x->key) {
                y->l = x->l;
                y->r = x;
                x->l = 0;
            } else {
                y->r = x->r;
                y->l = x;
                x->r = 0;
            }
            update_size(x);
            update_size(y);

            return y;
        }

        Tnode *_erase(Tnode *x, int key)
        {
            if (!x) return 0;

            x = splay(x, key);
            if (key == x->key) {
                if (x->cnt > 1) {
                    x->size--;
                    x->cnt--;
                    return x;
                }

                tree_size--;
                Tnode *y;
                if (!x->l) y = x->r;
                else {
                    y = splay(x->l, key);
                    y->r = x->r;
                    update_size(y);
                }

                return y;
            }

            return x;
        }

    public:
        Splay() { reset(); }
        bool empty() { return !root; }
        void insert(int key) { root = _insert(root, key); }
        void erase(int key)  { root = _erase(root, key); }

        void reset()
        {
            tree_size = 0;
            memset(buf, 0, sizeof(buf));
            buf_tail = buf;
            root = 0;
        }

        /* find the kth smallest one */
        int query(int k) const
        {
            Tnode *x = root;
            while (1 + 1 == 2) {
                if (x->l && x->l->size >= k) {
                    x = x->l;
                    continue;
                }
                if (x->l) k -= x->l->size;
                if (k <= x->cnt) return x->key;
                k -= x->cnt;
                x = x->r;
            }
        }
};

struct Query {
    int l, r, k;
    int id, ans;

    bool operator <(const Query &other) const
    {
        if (l == other.l) return r < other.r;
        return l < other.l;
    }
};
bool cmp_id(const Query &a, const Query &b) { return a.id < b.id; }

Splay splay;
int v[MAXN];
Query q[50010];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", v + i);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
        q[i].id = i;
    }
    sort(q, q + m);

    for (int i = q[0].l; i <= q[0].r; i++)
        splay.insert(v[i]);
    q[0].ans = splay.query(q[0].k);

    for (int i = 1; i < m; i++) {
        if (q[i - 1].r < q[i].l) {
            for (int j = q[i - 1].l; j <= q[i - 1].r; j++)
                splay.erase(v[j]);
            for (int j = q[i].l; j <= q[i].r; j++)
                splay.insert(v[j]);
        } else {
            for (int j = q[i - 1].l; j < q[i].l; j++)
                splay.erase(v[j]);
            if (q[i - 1].r < q[i].r) {
                for (int j = q[i - 1].r + 1; j <= q[i].r; j++)
                    splay.insert(v[j]);
            } else {
                for (int j = q[i].r + 1; j <= q[i - 1].r; j++)
                    splay.erase(v[j]);
            }
        }
        q[i].ans = splay.query(q[i].k);
    }

    sort(q, q + m, cmp_id);
    for (int i = 0; i < m; i++)
        printf("%d\n", q[i].ans);

    return 0;
}
