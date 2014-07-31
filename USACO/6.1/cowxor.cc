/*
ID: os.idea1
LANG: C++
TASK: cowxor
*/
#include <cstdio>
#include <cmath>
#include <algorithm>

using std::max;
using std::min;
using std::pair;

FILE *fin, *fout;

const int MAX_N = 100010;

int n, an[MAX_N], an_xor[MAX_N];

class Tree {
    private:
        static const int INF = 0x3f3f3f3f;
        int max_bit;

        struct Tnode {
            Tnode *l, *r; // l for 0 and r for 1
            int id;

            Tnode() : l(0), r(0), id(INF) { }
        };
        Tnode *root;

        void update(pair<int, int> *res, int *max_xor, const pair<int, int> &now) const
        {
            if (*max_xor < (an_xor[now.first] ^ an_xor[now.second])) {
                *res = now;
                *max_xor = (an_xor[now.first] ^ an_xor[now.second]);
                return ;
            }
            if (*max_xor == (an_xor[now.first] ^ an_xor[now.second]))
                if (max(res->first, res->second) > max(now.first, now.second)) *res = now;
        }

        pair<int, int> _query(Tnode *l, Tnode *r) const
        {
            if (l->id != INF) return pair<int, int>(l->id, r->id);

            int max_xor = 0;
            pair<int, int> res(0, 0);
            if (l->l && r->r) {
                pair<int, int> now = _query(l->l, r->r);
                update(&res, &max_xor, now);
            }
            if (l->r && r->l) {
                pair<int, int> now = _query(l->r, r->l);
                update(&res, &max_xor, now);
            }
            if (l->l && !l->r && r->l && !r->r) {
                pair<int, int> now = _query(l->l, r->l);
                update(&res, &max_xor, now);
            }
            if (!l->l && l->r && !r->l && r->r) {
                pair<int, int> now = _query(l->r, r->r);
                update(&res, &max_xor, now);
            }
            return res;
        }

    public:
        Tree()
        {
            root = new Tnode();
        }

        void set_bit(int _max_bit) { max_bit = _max_bit; }

        void insert(int p, int id)
        {
            Tnode *t = root;
            for (int i = max_bit - 1; i >= 0; i--) {
                if (p & (1 << i)) {
                    if (!t->r) t->r = new Tnode();
                    t = t->r;
                }
                else {
                    if (!t->l) t->l = new Tnode();
                    t = t->l;
                }
            }
            t->id = min(t->id, id);
        }

        pair<int, int> query() const
        {
            Tnode *t = root;
            while (!t->l || !t->r) {
                if (t->id != INF) return pair<int, int>(t->id, t->id);
                if (t->l) t = t->l;
                else t = t->r;
            }
            return _query(t->l, t->r);
        }
};
Tree an_tree;

int main()
{
    fin  = fopen("cowxor.in", "r");
    fout = fopen("cowxor.out", "w");

    fscanf(fin, "%d", &n);
    for (int i = 1; i <= n; i++)
        fscanf(fin, "%d", an + i);

    int max_bit = 1;
    for (int i = 1; i <= n; i++) {
        an_xor[i] = an_xor[i - 1] ^ an[i];
        max_bit = max(max_bit, (int)ceil(log2(an_xor[i] + 1)));
    }

    an_tree.set_bit(max_bit);
    for (int i = 1; i <= n; i++)
        an_tree.insert(an_xor[i], i);

    pair<int, int> ans = an_tree.query();
    int left = min(ans.first, ans.second), right = max(ans.first, ans.second);
    for (int i = right - 1; i >= left; i--)
        if (an_xor[i] == an_xor[left]) {
            left = i + 1;
            break;
        }

    pair<int, int> max_an(-1, 0);
    for (int i = 1; i <= n; i++)
        if (an[i] > max_an.first) max_an = pair<int, int>(an[i], i);
    if (max_an.first >= (an_xor[ans.first] ^ an_xor[ans.second]))
        left = right = max_an.second;

    fprintf(fout, "%d %d %d\n", an_xor[ans.first] ^ an_xor[ans.second], left, right);

    return 0;
}
