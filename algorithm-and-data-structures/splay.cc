/*
 *  SRC: POJ 2985
 * PROB: The k-th Largest Group
 * ALGO: Splay
 * DATE: Sep 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

/* TLE */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

const int MAX_N = 200010;

class Splay {
    private:
        const static int BUF_SIZE = MAX_N;
        int tree_size;

        struct Tnode {
            int key;
            int size, cnt;
            Tnode* l;
            Tnode* r;
        };

        int buf_cnt;
        Tnode buf[BUF_SIZE];
        Tnode* root;

        Tnode* get_max(Tnode* x) const
        {
            while (x->r) x = x->r;
            return x;
        }

        Tnode* get_min(Tnode* x) const
        {
            while (x->l) x = x->l;
            return x;
        }

        void update_size(Tnode* x)
        {
            x->size = x->cnt;
            if (x->l) x->size += x->l->size;
            if (x->r) x->size += x->r->size;
        }

        void update_larger_size(Tnode* x, const Tnode* end)
        {
            if (x == end) return ;
            update_larger_size(x->l, end);
            update_size(x);
        }

        void update_smaller_size(Tnode* x, const Tnode* end)
        {
            if (x == end) return ;
            update_smaller_size(x->r, end);
            update_size(x);
        }

        Tnode* left_rotate(Tnode* x)
        {
            Tnode* y = x->r;
            x->r = y->l;
            y->l = x;
            update_size(x);

            return y;
        }

        Tnode* right_rotate(Tnode* x)
        {
            Tnode* y = x->l;
            x->l = y->r;
            y->r = x;
            update_size(x);

            return y;
        }

        Tnode* splay(Tnode* x, int key)
        {
            if (!x) return x;

            Tnode* y = new Tnode;
            y->l = y->r = 0;
            Tnode* larger = y;
            Tnode* smaller = y;
            
            while (key != x->key) {
                if (key < x->key) {
                    if (x->l && key < x->l->key) x = right_rotate(x);
                    if (!x->l) break;
                    larger->l = x;
                    larger = x;
                    x = x->l;
                }
                else {  // key > x->key
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

        Tnode* _insert(Tnode* x, int key)
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
            Tnode* y = &buf[buf_cnt++];
            y->key = key;
            y->size = y->cnt = 1;
            y->l = y->r = 0;

            if (!x) return y;

            if (key < x->key) {
                y->l = x->l;
                y->r = x;
                x->l = 0;
            }
            else {
                y->r = x->r;
                y->l = x;
                x->r = 0;
            }
            update_size(x);
            update_size(y);

            return y;
        }

        Tnode* _erase(Tnode* x, int key)
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
                Tnode* y;
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
        Splay()
        {
            reset();
        }

        void reset()
        {
            tree_size = buf_cnt = 0;
            memset(buf, 0, sizeof(buf));
            root = 0;
        }

        bool empty()
        {
            return !root;
        }

        void insert(int key)
        {
            root = _insert(root, key);
        }

        void erase(int key)
        {
            root = _erase(root, key);
        }

        int query(int k)
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
