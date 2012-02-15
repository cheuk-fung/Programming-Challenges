/*
 *  SRC: POJ 2985
 * PROB: The k-th Largest Group
 * ALGO: Treap
 * DATE: Sep 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::swap;

const int MAXN = 200010;

class Treap {
    private:
        const static int BUF_SIZE = MAXN;
        int tree_size;

        struct Tnode {
            int key, fix;
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

        Tnode* left_rotate(Tnode* x)
        {
            Tnode* y = x->r;
            x->r = y->l;
            y->l = x;

            update_size(x);
            update_size(y);

            return y;
        }

        Tnode* right_rotate(Tnode* x)
        {
            Tnode* y = x->l;
            x->l = y->r;
            y->r = x;

            update_size(x);
            update_size(y);

            return y;
        }

        Tnode* _insert(Tnode* x, int key)
        {
            if (!x) {
                tree_size++;
                x = &buf[buf_cnt++];
                x->key = key;
                x->fix = rand() * rand();
                x->size = x->cnt = 1;
                x->l = x->r = 0;

                return x;
            }

            if (key < x->key) {
                x->l = _insert(x->l, key);
                if (x->l->fix > x->fix) x = right_rotate(x);
            }
            else if (key > x->key) {
                x->r = _insert(x->r, key);
                if (x->r->fix > x->fix) x = left_rotate(x);
            }
            else x->cnt++;

            update_size(x);

            return x;
        }

        Tnode* _erase(Tnode* x, int key)
        {
            if (!x) return 0;

            if (key < x->key) x->l = _erase(x->l, key);
            else if (key > x->key) x->r = _erase(x->r, key);
            else {
                if (x->cnt > 1) {
                    x->cnt--;
                    x->size--;
                    return x;
                }

                if (!x->l && !x->r) {
                    tree_size--;
                    return 0;
                }

                if (!x->l) x = left_rotate(x);
                else if (!x->r) x = right_rotate(x);
                else {
                    if (x->l->fix < x->r->fix) x = right_rotate(x);
                    else x = left_rotate(x);
                }
                x = _erase(x, key);
            }

            update_size(x);

            return x;
        }

    public:
        Treap()
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

Treap treap;

int fa[MAXN], fa_size[MAXN];

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
    treap.erase(fa_size[fa[x]]);
    treap.erase(fa_size[fa[y]]);
    int new_size = fa_size[fa[x]] + fa_size[fa[y]];
    treap.insert(new_size);
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
        treap.insert(1);
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
            printf("%d\n", treap.query(k));
        }
    }

    return 0;
}
