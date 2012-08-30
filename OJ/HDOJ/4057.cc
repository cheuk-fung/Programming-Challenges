/*
 *  SRC: HDOJ 4057
 * PROB: Rescue the Rabbit
 * ALGO: AC Automaton
 * DATE: Aug 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int NEGINF = 0xc0c0c0c0;

int gene[256];

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[4];
            Tnode *fail;
            int id;
        } node[1024];
        Tnode *root, *nodetail;

        int f[2][1024][1024];

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
        }

        void insert(char *s, int id)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[gene[*s]]) p->next[gene[*s]] = nodetail++;
                p = p->next[gene[*s++]];
            }
            p->id = id;
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
                Tnode *u = que.front();
                que.pop();
                for (int i = 0; i < 4; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        que.push(u->next[i]);
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        int query(int n, int l, int *w)
        {
            int curr = 0, res = NEGINF;
            memset(f, 0xc0, sizeof f);
            f[0][0][0] = 0;
            for (int i = 0; i < l; i++) {
                for (Tnode *u = node; u != nodetail; u++) {
                    for (int s = 0; s < 1 << n; s++) {
                        if (f[curr][u - node][s] == NEGINF) continue;

                        for (int j = 0; j < 4; j++) {
                            Tnode *p = u->next[j];

                            int ns = s, now = 0;
                            for (Tnode *t = p; t != root; t = t->fail) {
                                if (t->id) {
                                    if (!((ns >> (t->id - 1)) & 1)) {
                                        now += w[t->id];
                                        ns |= 1 << (t->id - 1);
                                    }
                                }
                            }
                            f[curr ^ 1][p - node][ns] = max(f[curr ^ 1][p - node][ns], f[curr][u - node][s] + now);
                            res = max(res, f[curr ^ 1][p - node][ns]);
                        }
                    }
                }
                memset(f[curr], 0xc0, sizeof f[curr]);
                curr ^= 1;
            }
            return res;
        }
} ac;

int w[100];
char strbuf[1000];

int main()
{
    gene['A'] = 0;
    gene['T'] = 1;
    gene['G'] = 2;
    gene['C'] = 3;

    int n, l;
    while (~scanf("%d%d", &n, &l)) {
        ac.build();
        for (int i = 1; i <= n; i++) {
            scanf("%s%d", strbuf, w + i);
            ac.insert(strbuf, i);
        }
        ac.build_fail();
        int r = ac.query(n, l, w);
        if (r >= 0) printf("%d\n", r);
        else puts("No Rabbit after 2012!");
    }

    return 0;
}

