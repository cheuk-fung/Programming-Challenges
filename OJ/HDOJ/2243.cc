/*
 *  SRC: HDOJ 2243
 * PROB: 考研路茫茫——单词情结
 * ALGO: AC Automaton + Matrix DP
 * DATE: Aug 30, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <stack>

using std::queue;

class Matrix {
    public:
        int n;
        unsigned long long a[50][50];

        Matrix(int _n) : n(_n) { memset(a, 0, sizeof a); }

        Matrix operator+(const Matrix &M) const
        {
            Matrix R = *this;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    R.a[i][j] += M.a[i][j];
                }
            }
            return R;
        }

        Matrix operator*(const Matrix &M) const
        {
            Matrix R(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        R.a[i][j] += a[i][k] * M.a[k][j];
                    }
                }
            }
            return R;
        }

        Matrix operator^(int k) const
        {
            Matrix R = *this;
            Matrix T = *this;
            for (k--; k; k >>= 1) {
                if (k & 1) R = R * T;
                T = T * T;
            }
            return R;
        }

        Matrix sum(int k) const
        {
            int bcnt = 31;
            while ((k >> bcnt) == 0) bcnt--;
            Matrix R = *this, M = *this;
            for (int i = bcnt - 1; i >= 0; i--) {
                if (k & (1 << i)) {
                    R = R + M * R + M * M * *this;
                    M = M * M * *this;
                } else {
                    R = R + M * R;
                    M = M * M;
                }
            }
            return R;
        }
};

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;
            bool exits;
        } node[50];
        Tnode *root, *nodetail;

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
        }

        void insert(char *s)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - 'a']) p->next[*s - 'a'] = nodetail++;
                p = p->next[*s++ - 'a'];
            }
            p->exits = true;
        }

        void build_fail()
        {
            queue<Tnode *> que;
            for (int i = 0; i < 26; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    que.push(root->next[i]);
                } else {
                    root->next[i] = root;
                }
            }

            while (!que.empty()) {
                Tnode *u = que.front();
                que.pop();
                u->exits |= u->fail->exits;
                for (int i = 0; i < 26; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        que.push(u->next[i]);
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        unsigned long long query(int l)
        {
            Matrix A(nodetail - node);
            for (Tnode *p = root; p != nodetail; p++) {
                if (p->exits) continue;
                for (int i = 0; i < 26; i++) {
                    if (p->next[i]->exits) continue;
                    A.a[p - node][p->next[i] - node]++;
                }
            }

            A = A.sum(l);
            unsigned long long r = 0;
            for (int i = 0; i < A.n; i++) {
                r += A.a[0][i];
            }

            return r;
        }
} ac;

unsigned long long gpow(unsigned long long a, unsigned long long b)
{
    unsigned long long r = 1;
    for ( ; b; b >>= 1) {
        if (b & 1) r *= a;
        a *= a;
    }
    return r;
}

int main()
{
    int n, l;
    while (~scanf("%d%d", &n, &l)) {
        ac.build();
        for (int i = 0; i < n; i++) {
            char str[10];
            scanf("%s", str);
            ac.insert(str);
        }
        ac.build_fail();
        unsigned long long r = ac.query(l);
        Matrix A(1);
        A.a[0][0] = 26;
        A = A.sum(l);
        r = A.a[0][0] - r;

        // printf("%llu\n", r);
        printf("%I64u\n", r);
    }

    return 0;
}

