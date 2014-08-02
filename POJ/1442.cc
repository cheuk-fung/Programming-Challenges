/*
 *  SRC: POJ 1442
 * PROB: Black Box
 * ALGO: Treap
 * DATE: Sep 23, 2011 
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

const int MAX_N = 30010;

class Treap {
    private:
        const static int BUF_SIZE = MAX_N;
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

Treap treap;
int A[MAX_N], u[MAX_N];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", A + i);
    for (int i = 0; i < m; i++) scanf("%d", u + i);

    for (int i = 0, j = 0, cnt = 0; j < m; i++) {
        treap.insert(A[i]);
        while (u[j] == i + 1) {
            printf("%d\n", treap.query(++cnt));
            j++;
        }
    }

    return 0;
}
