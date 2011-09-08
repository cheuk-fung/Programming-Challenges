/*
 *  SRC: POJ 3481
 * PROB: Double Queue
 * ALGO: Treap
 * DATE: Sep 04, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <utility>

using std::pair;

class Treap {
    private:
        const static int BUF_SIZE = 1000010;
        int size;

        struct Node {
            int key, fix;
            int id;
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

        Node* left_rotate(Node* x)
        {
            Node* y = x->r;
            x->r = y->l;
            y->l = x;
            return y;
        }

        Node* right_rotate(Node* x)
        {
            Node* y = x->l;
            x->l = y->r;
            y->r = x;
            return y;
        }

        Node* _insert(Node* x, int key, int id)
        {
            if (!x) {
                size++;
                x = &buf[buf_cnt++];
                x->key = key;
                x->fix = rand() * rand();
                x->id = id;
                x->l = x->r = 0;

                return x;
            }

            if (key < x->key) {
                x->l = _insert(x->l, key, id);
                if (x->l->fix > x->fix) x = right_rotate(x);
            }
            else {
                x->r = _insert(x->r, key, id);
                if (x->r->fix > x->fix) x = left_rotate(x);
            }

            return x;
        }

        Node* _erase(Node* x, int key)
        {
            if (!x) return 0;

            if (key < x->key) x->l = _erase(x->l, key);
            else if (key > x->key) x->r = _erase(x->r, key);
            else {
                if (!x->l && !x->r) {
                    size--;
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

            return x;
        }

    public:
        Treap()
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

        void insert(int key, int id)
        {
            root = _insert(root, key, id);
        }

        void erase(int key)
        {
            root = _erase(root, key);
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

Treap treap;

int main()
{
    int order;
    while (scanf("%d", &order), order) {
        switch(order) {
            case 0: return 0;
            case 1: {
                        int key, id;
                        scanf("%d%d", &id, &key);
                        treap.insert(key, id);
                        break;
                    }
            case 2: {
                        if (treap.empty()) puts("0");
                        else {
                            pair<int, int> ans = treap.find_max();
                            printf("%d\n", ans.second);
                            treap.erase(ans.first);
                        }
                        break;
                    }
            case 3: {
                        if (treap.empty()) puts("0");
                        else {
                            pair<int, int> ans = treap.find_min();
                            printf("%d\n", ans.second);
                            treap.erase(ans.first);
                        }
                    }
        }
    }

    return 0;
}
