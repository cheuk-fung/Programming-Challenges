/*
 *  SRC: POJ 2985
 * PROB: The k-th Largest Group
 * ALGO: Splay
 * DATE: Sep 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

const int MAX_N = 200010;

class Splay {
    private:
        enum { BUF_SIZE = MAX_N };
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
                    y->r = x->r;
                    if (x->r) x->r->p = y;
                    push_up(y);
                }

                tree_size--;
            }
        }

        int query(int k) const
        {
            Tnode* x = root;
            while (1 + 1 == 2) {
                if (x->r && x->r->size >= k) {
                    x = x->r;
                    continue;
                }
                if (x->r) k -= x->r->size;
                if (k <= x->cnt) return x->key;
                k -= x->cnt;
                x = x->l;
            }
        }
};

Splay splay;

int fa[MAX_N], fa_size[MAX_N];

int get_father(int u)
{
    if (fa[u] == u) return u;

    return fa[u] = get_father(fa[u]);
}

void ds_union(int u, int v)
{
    int x = get_father(u);
    int y = get_father(v);
    if (x != y) fa[x] = y;
}

void combine(int x, int y)
{
    if (get_father(x) == get_father(y)) return ;
    splay.erase(fa_size[fa[x]]);
    splay.erase(fa_size[fa[y]]);
    int new_size = fa_size[fa[x]] + fa_size[fa[y]];
    splay.insert(new_size);
    ds_union(x, y);
    fa_size[get_father(x)] = new_size;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        fa_size[i] = 1;
        splay.insert(1);
    }

    int c, i, j, k;
    while (m--) {
        scanf("%d", &c);
        if (!c) {
            scanf("%d%d", &i, &j);
            combine(i, j);
        }
        else {
            scanf("%d", &k);
            printf("%d\n", splay.query(k));
        }
    }

    return 0;
}
