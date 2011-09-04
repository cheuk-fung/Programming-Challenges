/*
 *  SRC: POJ 3481
 * PROB: Double Queue
 * ALGO: Splay
 * DATE: Sep 04, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <utility>

using std::pair;

class Splay {
    private:
        const static int BUF_SIZE = 1000010;
        int size;

        struct Node {
            int key;
            int id;
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

        void _insert(Node* x, Node* p, bool is_left, int key, int id)
        {
            if (!x) {
                size++;
                x = &buf[buf_cnt++];
                x->key = key;
                x->id = id;
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

            if (key < x->key) _insert(x->l, x, 1, key, id);
            else _insert(x->r, x, 0, key, id);
        }

        void _erase(Node* x, int key)
        {
            if (!x) return ;

            if (key < x->key) _erase(x->l, key);
            else if (key > x->key) _erase(x->r, key);
            else {
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

        void insert(int key, int id)
        {
            _insert(root, 0, 0, key, id);
        }

        void erase(int key)
        {
            _erase(root, key);
        }

        pair<int, int> find_max() const
        {
            Node* x = get_max(root);
            return pair<int, int>(x->key, x->id);
        }

        pair<int, int> find_min() const
        {
            Node* x = get_min(root);
            return pair<int, int>(x->key, x->id);
        }
};

Splay splay;

int main()
{
    int order;
    while (scanf("%d", &order), order) {
        switch(order) {
            case 0: return 0;
            case 1: {
                        int key, id;
                        scanf("%d%d", &id, &key);
                        splay.insert(key, id);
                        break;
                    }
            case 2: {
                        if (splay.empty()) puts("0");
                        else {
                            pair<int, int> ans = splay.find_max();
                            printf("%d\n", ans.second);
                            splay.erase(ans.first);
                        }
                        break;
                    }
            case 3: {
                        if (splay.empty()) puts("0");
                        else {
                            pair<int, int> ans = splay.find_min();
                            printf("%d\n", ans.second);
                            splay.erase(ans.first);
                        }
                    }
        }
    }

    return 0;
}
