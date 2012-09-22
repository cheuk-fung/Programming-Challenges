/*
 *  SRC: HDOJ 4125
 * PROB: Moles
 * ALGO: BST
 * DATE: Sep 21, 2012
 * COMP: C++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

const int MAXN = 600010;
char s[MAXN << 2], t[7010];
char *stail;
int prn[7010];

class BST {
    private:
        struct Tnode {
            int v;
            Tnode *lc, *rc;
        } nbuf[MAXN];
        Tnode *root, *ntail;
        Tnode *where[MAXN];

    public:
        void build()
        {
            memset(nbuf, 0, sizeof nbuf);
            ntail = nbuf;
            root = ntail++;
        }

        void insert(int v, int index, set<int> &a)
        {
            if (index == 0) {
                root->v = v;
                where[v] = root;
                return ;
            }

            set<int>::iterator lp = a.lower_bound(v);
            set<int>::iterator rp = a.upper_bound(v);
            if (lp == a.begin()) {
                Tnode *p = where[*rp];
                assert(p->lc == 0);
                p->lc = ntail++;
                p->lc->v = v;
                where[v] = p->lc;
            } else if (rp == a.end()) {
                Tnode *p = where[*--lp];
                assert(p->rc == 0);
                p->rc = ntail++;
                p->rc->v = v;
                where[v] = p->rc;
            } else {
                Tnode *p = where[*--lp], *q = where[*rp];
                if (p->rc != 0) {
                    assert(q->lc == 0);
                    q->lc = ntail++;
                    q->lc->v = v;
                    where[v] = q->lc;
                } else {
                    assert(p->rc == 0);
                    p->rc = ntail++;
                    p->rc->v = v;
                    where[v] = p->rc;
                }
            }
        }

        void query()
        {
            stack<Tnode *> S;
            stack<int> next;

            S.push(root);
            next.push(0);
            while (!S.empty()) {
                Tnode *p = S.top();
                int now = next.top();
                S.pop();
                next.pop();

                *stail++ = p->v & 1 ? '1' : '0';
                if (now == 0) {
                    if (p->lc != 0) {
                        S.push(p);
                        next.push(1);
                        S.push(p->lc);
                        next.push(0);
                    } else {
                        now = 1;
                    }
                }
                if (now == 1 && p->rc != 0) {
                    S.push(p);
                    next.push(2);
                    S.push(p->rc);
                    next.push(0);
                }
            }

            *stail++ = 0;
        }
} bst;

void kmpinit(char *b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != b[i]) j = prn[j - 1];
        if (b[j] == b[i]) j++;
        prn[i] = j;
    }
}

int kmp(char *a, int n, char *b, int m)
{
    int cnt = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && b[j] != a[i]) j = prn[j - 1];
        if (b[j] == a[i]) j++;
        if (j == m) {
            cnt++;
            j = prn[j - 1];
        }
    }
    return cnt;
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        set<int> a;
        bst.build();
        stail = s;

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            a.insert(v);
            bst.insert(v, i, a);
        }
        bst.query();
        // printf("%s\n", s);

        scanf("%s", t);
        int slen = stail - s, tlen = strlen(t);
        kmpinit(t, tlen);
        int r = kmp(s, slen, t, tlen);
        printf("Case #%d: %d\n", task, r);
    }

    return 0;
}

