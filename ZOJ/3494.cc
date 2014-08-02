/*
 *  SRC: ZOJ 3494
 * PROB: BCD Code
 * ALGO: AC Automaton
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MOD = 1000000009;
const char BCD[10][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};

class ACAutomaton {
    private:
        struct Tnode {
            Tnode *next[2];
            Tnode *fail;
            bool tag;
        } tbuf[2012];
        Tnode *root, *tail;

        int f[209][2012];
        int g[209][2012];

    public:
        void build()
        {
            memset(tbuf, 0, sizeof tbuf);
            tail = tbuf;
            root = tail++;
        }

        void insert(const char *s)
        {
            Tnode *p = root;
            while (*s) {
                int idx = *s++ - '0';
                if (p->next[idx] == 0) p->next[idx] = tail++;
                p = p->next[idx];
            }
            p->tag = true;
        }

        void build_fail()
        {
            queue<Tnode *> Q;
            for (int i = 0; i < 2; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    Q.push(root->next[i]);
                } else {
                    root->next[i] = root;
                }
            }

            while (!Q.empty()) {
                Tnode *p = Q.front();
                Q.pop();
                p->tag |= p->fail->tag;
                for (int i = 0; i < 2; i++) {
                    if (p->next[i]) {
                        p->next[i]->fail = p->fail->next[i];
                        Q.push(p->next[i]);
                    } else {
                        p->next[i] = p->fail->next[i];
                    }
                }
            }
        }

        Tnode *walk(Tnode *p, const char *s)
        {
            while (*s) {
                p = p->next[*s++ - '0'];
                if (p->tag) return 0;
            }
            return p;
        }

        int query(const char *str)
        {
            int res = walk(root, BCD[0]) ? 1 : 0;
            int len = strlen(str);

            memset(f, 0, sizeof f);
            f[0][0] = 1;
            for (int i = 0; i < len - 1; i++) {
                for (Tnode *s = root; s != tail; s++) {
                    if (!f[i][s - root]) continue;
                    for (int k = (i == 0 ? 1 : 0); k < 10; k++) {
                        Tnode *t = walk(s, BCD[k]);
                        if (!t) continue;
                        f[i + 1][t - root] = (f[i + 1][t - root] + f[i][s - root]) % MOD;
                        res = (res + f[i][s - root]) % MOD;
                    }
                }
            }

            memset(f, 0, sizeof f);
            memset(g, 0, sizeof g);
            g[0][0] = 1;
            for (int i = 0; i < len; i++) {
                for (Tnode *s = root; s != tail; s++) {
                    if (f[i][s - root]) {
                        for (int k = (i == 0 ? 1 : 0); k < 10; k++) {
                            Tnode *t = walk(s, BCD[k]);
                            if (!t) continue;
                            f[i + 1][t - root] = (f[i + 1][t - root] + f[i][s - root]) % MOD;
                        }
                    }
                    if (g[i][s - root]) {
                        for (int k = (i == 0 ? 1 : 0); k < str[i] - '0'; k++) {
                            Tnode *t = walk(s, BCD[k]);
                            if (!t) continue;
                            f[i + 1][t - root] = (f[i + 1][t - root] + g[i][s - root]) % MOD;
                        }
                        Tnode *t = walk(s, BCD[str[i] - '0']);
                        if (t) {
                            g[i + 1][t - root] = (g[i + 1][t - root] + g[i][s - root]) % MOD;
                        }
                    }
                }
            }
            for (Tnode *s = root; s != tail; s++) {
                res = (res + f[len][s - root]) % MOD;
            }

            return res;
        }
} ac;

char str[22], A[209], B[209];

void inc(char *s)
{
    int len = strlen(s);
    s[len - 1]++;
    for (int i = len - 1; i > 0 && s[i] > '9'; i--) {
        assert(s[i] == '9' + 1);
        s[i] = '0';
        s[i - 1]++;
    }
    if (s[0] == '9' + 1) {
        s[0] = '0';
        for (int i = len; i > 0; i--) {
            s[i] = s[i - 1];
        }
        s[0] = '1';
        s[++len] = '\0';
    }
}

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        ac.build();

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            ac.insert(str);
        }
        ac.build_fail();

        scanf("%s", A);
        scanf("%s", B);
        inc(B);
        int Aret = ac.query(A);
        int Bret = ac.query(B);
        // printf("%d %d\n", Aret, Bret);
        printf("%d\n", ((Bret - Aret) % MOD + MOD) % MOD);
    }

    return 0;
}

