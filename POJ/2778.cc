/*
 *  SRC: POJ 2778
 * PROB: DNA Sequence
 * ALGO: AC Automata
 * DATE: Aug 03, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MOD = 100000;

inline int gene2num(char c)
{
    int r;
    switch (c) {
        case 'A': r = 0; break;
        case 'G': r = 1; break;
        case 'T': r = 2; break;
        case 'C': r = 3;
    }
    return r;
}

class Matrix {
    public:
        long long M[100][100];
        int n; // n * n

        Matrix &operator*=(Matrix &);
} F, T, R;

Matrix &Matrix::operator*=(Matrix &O)
{
    memset(R.M, 0, sizeof M);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                R.M[i][j] = (R.M[i][j] + M[i][k] * O.M[k][j]) % MOD;
            }
        }
    }
    memmove(M, R.M, sizeof M);
    return *this;
}

class ACAutomata {
    private:
        struct Tnode {
            Tnode *next[4];
            Tnode *fail;
            int idx;
        };
        Tnode node[100];
        Tnode *root, *nodetail;

    public:
        ACAutomata() : root(node), nodetail(node + 1) { }

        void insert(char *s, int idx)
        {
            Tnode *p = root;
            while (*s) {
                int gene = gene2num(*s++);
                if (!p->next[gene]) {
                    p->next[gene] = nodetail++;
                }
                p = p->next[gene];
            }
            p->idx = idx;
        }

        void build_fail()
        {
            queue<Tnode *> que;
            for (int i = 0; i < 4; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    que.push(root->next[i]);
                } else {
                    root->next[i] = root;
                }
            }

            while (!que.empty()) {
                Tnode *curr = que.front();
                que.pop();
                for (int i = 0; i < 4; i++) {
                    if (curr->next[i]) {
                        curr->next[i]->fail = curr->fail->next[i];
                        que.push(curr->next[i]);
                    } else {
                        curr->next[i] = curr->fail->next[i];
                    }
                }

                if (!curr->idx) curr->idx = curr->fail->idx;
            }
        }

        int query(int n)
        {
            T.n = nodetail - node;
            for (Tnode *p = root; p != nodetail; p++) {
                if (p->idx) continue;
                for (int i = 0; i < 4; i++) {
                    if (p->next[i]->idx) continue;
                    T.M[p - node][p->next[i] - node]++;
                }
            }

            F = T;
            n--;
            while (n) {
                if (n & 1) F *= T;
                T *= T;
                n >>= 1;
            }

            int ans = 0;
            for (int i = 0; i < F.n; i++) {
                ans = (ans + F.M[0][i]) % MOD;
            }
            return ans;
        }
} ac;

char strbuf[16];

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%s", strbuf);
        ac.insert(strbuf, i + 1);
    }
    ac.build_fail();

    int r = ac.query(n);
    printf("%d\n", r);

    return 0;
}

