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

const int MAX_N = 100010;

class Splay {
    private:
        const static int BUF_SIZE = MAX_N;
        int tree_size;

        struct Node {
            int key;
            int size, cnt;
            Node* l;
            Node* r;
        };

        int buf_cnt;
        Node buf[BUF_SIZE];
        Node* root;

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

            tree_size++;
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

                tree_size--;
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

        int search(int k)
        {
            Node* x = root;
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
int v[MAX_N];
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
    q[0].ans = splay.search(q[0].k);

    for (int i = 1; i < m; i++) {
        if (q[i - 1].r < q[i].l) {
            for (int j = q[i - 1].l; j <= q[i - 1].r; j++)
                splay.erase(v[j]);
            for (int j = q[i].l; j <= q[i].r; j++)
                splay.insert(v[j]);
        }
        else {
            for (int j = q[i - 1].l; j < q[i].l; j++)
                splay.erase(v[j]);
            if (q[i - 1].r < q[i].r)
                for (int j = q[i - 1].r + 1; j <= q[i].r; j++)
                    splay.insert(v[j]);
            else
                for (int j = q[i].r + 1; j <= q[i - 1].r; j++)
                    splay.erase(v[j]);
        }
        q[i].ans = splay.search(q[i].k);
    }

    sort(q, q + m, cmp_id);
    for (int i = 0; i < m; i++)
        printf("%d\n", q[i].ans);

    return 0;
}
