/*
 *  SRC: HDOJ 4441
 * PROB: Queue Sequence
 * ALGO: Splay
 * DATE: Nov 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

class Segment_tree {
    private:
        static int lep, rep;

        int mn[MAXN << 3];

        int LC(int x) { return x << 1; }
        int RC(int x) { return x << 1 | 1; }

        void pushup(int x)
        {
            mn[x] = min(mn[LC(x)], mn[RC(x)]);
        }

    public:
        void build(int a, int b)
        {
            lep = a;
            rep = b;
            memset(mn, 0x3f, sizeof mn);
        }

        void update(int c, int v, int a = lep, int b = rep, int idx = 1)
        {
            if (a + 1 == b) {
                if (v == 1) mn[idx] = a;
                else mn[idx] = INF;
                return ;
            }

            int mid = (a + b) >> 1;
            if (c < mid) update(c, v, a, mid, LC(idx));
            else update(c, v, mid, b, RC(idx));
            pushup(idx);
        }

        int query() const { return mn[1]; }
} st;
int Segment_tree::lep, Segment_tree::rep;

struct Tnode {
    int key;
    long long sum;
    int size, positive, negative;
    Tnode *p, *l, *r;
} nodebuf[MAXN << 1];

int n;
char opr[10];
Tnode *pos[MAXN << 1];

class Splay {
    public:
        Tnode *root, *buftail;

        Tnode *getmax(Tnode *x) const
        {
            while (x->r) x = x->r;
            return x;
        }

        Tnode *getmin(Tnode *x) const
        {
            while (x->l) x = x->l;
            return x;
        }

        void pushup(Tnode *x)
        {
            x->size = 1;
            if (x->l) x->size += x->l->size;
            if (x->r) x->size += x->r->size;

            x->positive = x->key > 0;
            if (x->l) x->positive += x->l->positive;
            if (x->r) x->positive += x->r->positive;

            x->negative = x->key < 0;
            if (x->l) x->negative += x->l->negative;
            if (x->r) x->negative += x->r->negative;

            x->sum = x->key;
            if (x->l) x->sum += x->l->sum;
            if (x->r) x->sum += x->r->sum;
        }

        Tnode *lro(Tnode *x)
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
            pushup(x);
            return y;
        }

        Tnode *rro(Tnode *x)
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
            pushup(x);
            return y;
        }

        Tnode *splay(Tnode *x, Tnode *p)
        {
            while (x->p != p) {
                Tnode *y = x->p, *z = y->p;
                if (z == p) {
                    x = x == y->l ? rro(y) : lro(y);
                } else if (y == z->l) {
                    x = x == y->l ? (rro(z), rro(y)) : (lro(y), rro(z));
                } else {
                    x = x == y->l ? (rro(y), lro(z)) : (lro(z), lro(y));
                }
            }
            pushup(x);
            return x;
        }

        Tnode *find(int p)
        {
            Tnode *x = root;
            while (p) {
                if (x->l && x->l->size >= p) {
                    x = x->l;
                } else {
                    if (x->l) p -= x->l->size;
                    p--;
                    if (p) x = x->r;
                }
            }
            return x;
        }

        Tnode *nextnode(int key)
        {
            Tnode *x = buftail++;
            x->key = key;
            x->sum = key;
            x->size = 1;
            x->positive = key > 0;
            x->negative = key < 0;
            x->p = x->l = x->r = 0;
            return x;
        }

    public:
        Splay() { build(); }
        void build()
        {
            buftail = nodebuf;
            root = nextnode(0);
            root->r = nextnode(0);
            root->r->p = root;
        }

        void find_insert(int p, int key)
        {
            Tnode *y = nextnode(key);
            pos[key > 0 ? key : -key + n] = y;

            root = splay(find(p + 1), 0);
            Tnode *x = splay(find(p), root);
            x->r = y;
            y->p = x;
            pushup(x);
            pushup(root);

            root = splay(y, 0);
        }

        void insert(int p, int key)
        {
            find_insert(p, key);
            int cnt = root->l->positive + 1;
            if (cnt > root->negative) {
                find_insert(root->size - 1, -key);
            } else {
                Tnode *x = root;
                p = 0;
                while (cnt) {
                    if (x->l && x->l->negative >= cnt) {
                        x = x->l;
                    } else {
                        if (x->l) {
                            cnt -= x->l->negative;
                            p += x->l->size;
                        }
                        if (x->key < 0) cnt--;
                        p++;
                        if (cnt) x = x->r;
                    }
                }
                find_insert(p - 1, -key);
            }
        }

        void erase(Tnode *x)
        {
            root = x = splay(x, 0);
            if (!x->l) {
                root = x->r;
                if (root) root->p = 0;
            } else {
                Tnode *y = getmax(x->l);
                root = y = splay(y, x);
                root->p = 0;
                y->r = x->r;
                if (x->r) x->r->p = y;
                pushup(y);
            }
        }

        long long query(int key)
        {
            root = splay(pos[key], 0);
            Tnode *x = splay(pos[key + n], root);
            pushup(root);
            return x->l ? x->l->sum : 0;
        }
} splay;

int main()
{
    int tasks = 1;
    while (~scanf("%d", &n)) {
        printf("Case #%d:\n", tasks++);

        splay.build();
        st.build(1, n + 1);
        for (int i = 1; i <= n; i++) st.update(i, 1);
        for (int i = 0; i < n; i++) {
            int p;
            scanf("%s%d", opr, &p);
            if (opr[0] == 'i') {
                int key = st.query();
                splay.insert(p + 1, key);
                assert(key <= n);
                st.update(key, -1);
            } else if (opr[0] == 'r') {
                st.update(p, 1);
                splay.erase(pos[p]);
                splay.erase(pos[p + n]);
            } else {
                long long res = splay.query(p);
                // printf("%lld\n", res);
                printf("%I64d\n", res);
            }
        }
    }

    return 0;
}

