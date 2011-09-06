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

        void update_larger_size(Node* x, const Node* end)
        {
            if (x == end) return ;
            update_larger_size(x->l, end);
            update_size(x);
        }

        void update_smaller_size(Node* x, const Node* end)
        {
            if (x == end) return ;
            update_smaller_size(x->r, end);
            update_size(x);
        }

        Node* left_rotate(Node* x)
        {
            Node* y = x->r;
            x->r = y->l;
            y->l = x;
            update_size(x);

            return y;
        }

        Node* right_rotate(Node* x)
        {
            Node* y = x->l;
            x->l = y->r;
            y->r = x;
            update_size(x);

            return y;
        }

        Node* splay(Node* x, int key)
        {
            if (!x) return x;

            Node* y = new Node;
            y->l = y->r = 0;
            Node* larger = y;
            Node* smaller = y;
            
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

        Node* _insert(Node* x, int key)
        {
            if (x) {
                x = splay(x, key);
                if (key == x->key) {
                    x->size++;
                    x->cnt++;
                    return x;
                }
            }

            size++;
            Node* y = &buf[buf_cnt++];
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

        Node* _erase(Node* x, int key)
        {
            if (!x) return 0;

            x = splay(x, key);
            if (key == x->key) {
                if (x->cnt > 1) {
                    x->size--;
                    x->cnt--;
                    return x;
                }

                size--;
                Node* y;
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
            size = buf_cnt = 0;
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
