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
        int size;

        struct Node {
            int key;
            int size, cnt;
            Node* p;
            Node* l;
            Node* r;
        };

        int buf_cnt;
        Node buf[BUF_SIZE];
        Node* root;

        Node* get_max(Node* x) const
        {
            while (x->r) x = x->r;
            return x;
        }

        Node* get_min(Node* x) const
        {
            while (x->l) x = x->l;
            return x;
        }

        void update_size(Node* x)
        {
            x->size = x->cnt;
            if (x->l) x->size += x->l->size;
            if (x->r) x->size += x->r->size;
        }

        void update_tree_size(Node* x)
        {
            while (x) {
                update_size(x);
                x = x->p;
            }
        }

        void left_rotate(Node* x)
        {
            Node* y = x->r;
            x->r = y->l;
            if (y->l) y->l->p = x;
            y->l = x;

            if (x->p) {
                if (x == x->p->l) x->p->l = y;
                else x->p->r = y;
            }
            else root = y;

            y->p = x->p;
            x->p = y;

            update_size(x);
            update_size(y);
        }

        void right_rotate(Node* x)
        {
            Node* y = x->l;
            x->l = y->r;
            if (y->r) y->r->p = x;
            y->r = x;

            if (x->p) {
                if (x == x->p->l) x->p->l = y;
                else x->p->r = y;
            }
            else root = y;

            y->p = x->p;
            x->p = y;

            update_size(x);
            update_size(y);
        }

        void splay(Node* x)
        {
            if (x == root) return ;

            if (x->p == root) {
                if (x == root->l) right_rotate(root);
                else left_rotate(root);
            }
            else {
                Node* p = x->p;
                Node* g = p->p;
                if (x == p->l && p == g->l) {
                    right_rotate(g);
                    right_rotate(p);
                }
                else if (x == p->r && p == g->r) {
                    left_rotate(g);
                    left_rotate(p);
                }
                else if (x == p->l && p == g->r) {
                    right_rotate(p);
                    left_rotate(g);
                }
                else {
                    left_rotate(p);
                    right_rotate(g);
                }
            }

            splay(x);
        }

        void _insert(Node* x, Node* p, bool is_left, int key)
        {
            if (!x) {
                size++;
                x = &buf[buf_cnt++];
                x->key = key;
                x->size = x->cnt = 1;
                x->p = p;
                x->l = x->r = 0;

                if (p) {
                    if (is_left) p->l = x;
                    else p->r = x;
                }
                else root = x;

                splay(x);

                return ;
            }

            if (key < x->key) _insert(x->l, x, 1, key);
            else if (key > x->key) _insert(x->r, x, 0, key);
            else {
                x->cnt++;
                splay(x);
            }
        }

        void _erase(Node* x, int key)
        {
            if (!x) return ;

            if (key < x->key) _erase(x->l, key);
            else if (key > x->key) _erase(x->r, key);
            else {
                if (x->cnt > 1) {
                    x->cnt--;
                    x->size--;

                    splay(x);

                    return ;
                }

                Node* y;
                if (x == root) {
                    if (size == 1) {
                        size = 0;
                        root = 0;
                        return ;
                    }

                    if (x->l) y = get_max(x->l);
                    else y = get_min(x->r);
                    splay(y);
                    _erase(root, key);

                    return ;
                }

                size--;
                if (!x->l && !x->r) {
                    if (x == x->p->l) x->p->l = 0;
                    else x->p->r = 0;
                    y = x;
                }
                else {
                    if (!x->l) y = x->r;
                    else if (!x->r) y = x->l;
                    else {
                        y = get_max(x->l);

                        y->r = x->r;
                        x->r->p = y;
                        if (y->p != x) {
                            y->p->r = y->l;
                            if (y->l) y->l->p = y->p;
                            y->l = x->l;
                            x->l->p = y;
                        }
                    }
                    if (x == x->p->l) x->p->l = y;
                    else x->p->r = y;
                    update_tree_size(y->p);
                    y->p = x->p;
                }

                splay(y->p);
            }
        }

    public:
        Splay()
        {
            reset();
        }

        void reset()
        {
            size = buf_cnt = 0;
            memset(buf, 0, sizeof(buf));
            root = 0;
        }

        bool empty()
        {
            return !size;
        }

        void insert(int key)
        {
            _insert(root, 0, 0, key);
        }

        void erase(int key)
        {
            _erase(root, key);
        }

        int search(int k)
        {
            Node* x = root;
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
            printf("%d\n", splay.search(k));
        }
    }

    return 0;
}
