/*
 *  SRC: POJ 2761
 * PROB: Feed the dogs
 * ALGO: Splay
 * DATE: Sep 08, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;
using std::sort;

const int MAXN = 100010;

class Splay {
    private:
        enum { BUF_SIZE = MAXN };
        int tree_size;

        struct Tnode {
            int key;
            int size, cnt;
            Tnode *p, *l, *r;
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

        Tnode *find(int key, Tnode **p)
        {
            Tnode *x = root;
            *p = 0;
            while (x && x->key != key) {
                *p = x;
                if (key < x->key) x = x->l;
                else x = x->r;
            }
            return x;
        }

        void push_up(Tnode *x)
        {
            x->size = x->cnt;
            if (x->l) x->size += x->l->size;
            if (x->r) x->size += x->r->size;
        }

        Tnode *left_rotate(Tnode *x)
        {
            Tnode *y = x->r;
            y->p = x->p;
            if (x->p) {
                if (x == x->p->l) x->p->l = y;
                else x->p->r = y;
            }
            x->r = y->l;
            if (x->r) x->r->p = x;
            y->l = x;
            x->p = y;
            push_up(x);
            return y;
        }

        Tnode *right_rotate(Tnode *x)
        {
            Tnode *y = x->l;
            y->p = x->p;
            if (x->p) {
                if (x == x->p->l) x->p->l = y;
                else x->p->r = y;
            }
            x->l = y->r;
            if (x->l) x->l->p = x;
            y->r = x;
            x->p = y;
            push_up(x);
            return y;
        }

        Tnode *splay(Tnode *x, Tnode *p) // splay x to be p's child
        {
            while (x->p != p) {
                Tnode *y = x->p, *z = y->p;
                if (z == p) {
                    x = x == y->l ? right_rotate(y) : left_rotate(y);
                } else if (y == z->l) {
                    x = x == y->l ? (right_rotate(z), right_rotate(y)) : (left_rotate(y), right_rotate(z));
                } else {
                    x = x == y->l ? (right_rotate(y), left_rotate(z)) : (left_rotate(z), left_rotate(y));
                }
            }
            push_up(x);

            return x;
        }

    public:
        Splay() { reset(); }
        bool empty() { return !root; }

        void reset()
        {
            tree_size = 0;
            memset(buf, 0, sizeof(buf));
            buf_tail = buf;
            root = 0;
        }

        void insert(int key)
        {
            Tnode *p, *x = find(key, &p);
            if (x) {
                root = x = splay(x, 0);
                x->cnt++;
                x->size++;
                return ;
            }

            x = buf_tail++;
            x->key = key;
            x->cnt = x->size = 1;
            x->p = p;
            x->l = x->r = 0;
            if (p) {
                if (key < p->key) p->l = x;
                else p->r = x;
            }
            root = x = splay(x, 0);
            assert(x->p == 0);

            tree_size++;
        }

        void erase(int key)
        {
            Tnode *p, *x = find(key, &p);
            if (x) {
                root = x = splay(x, 0);
                if (x->cnt > 1) {
                    x->cnt--;
                    x->size--;
                    return ;
                }

                if (!x->l) {
                    root = x->r;
                    if (root) root->p = 0;
                } else {
                    Tnode *y = get_max(x->l);
                    root = y = splay(y, x);
                    root->p = 0;
                    assert(y->r == 0);
                    y->r = x->r;
                    if (x->r) x->r->p = y;
                    push_up(y);
                }

                tree_size--;
            }
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
        return l == other.l ? r < other.r : l < other.l;
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

    for (int i = q[0].l; i <= q[0].r; i++) splay.insert(v[i]);
    q[0].ans = splay.query(q[0].k);

    for (int i = 1; i < m; i++) {
        if (q[i - 1].r < q[i].l) {
            for (int j = q[i - 1].l; j <= q[i - 1].r; j++) splay.erase(v[j]);
            for (int j = q[i].l; j <= q[i].r; j++) splay.insert(v[j]);
        } else {
            for (int j = q[i - 1].l; j < q[i].l; j++) splay.erase(v[j]);
            for (int j = q[i - 1].r + 1; j <= q[i].r; j++) splay.insert(v[j]);
        }
        q[i].ans = splay.query(q[i].k);
    }

    sort(q, q + m, cmp_id);
    for (int i = 0; i < m; i++)
        printf("%d\n", q[i].ans);

    return 0;
}
