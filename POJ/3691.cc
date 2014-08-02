/*
 *  SRC: POJ 3691
 * PROB: DNA repair
 * ALGO: AC Automaton
 * DATE: Sep 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
int gene[256];

inline int MIN(int x, int y) { return x < y ? x : y; }

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[4];
            Tnode *fail;
            bool tag;
        };
        Tnode node[1024];
        Tnode *root, *nodetail;
        int f[2][1024];

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
                int idx = gene[*s++];
                if (!p->next[idx]) p->next[idx] = nodetail++;
                p = p->next[idx];
            }
            p->tag = true;
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
                u->tag |= u->fail->tag;
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

        int query(char *s)
        {
            int curr = 0, next = 1;
            memset(f, 0x3f, sizeof f);
            f[curr][0] = 0;
            while (*s) {
                int idx = gene[*s++];
                for (Tnode *u = root; u != nodetail; u++) {
                    if (u->tag || f[curr][u - node] == INF) continue;
                    for (int i = 0; i < 4; i++) {
                        Tnode *p = u->next[i];
                        if (p->tag) continue;
                        f[next][p - node] = MIN(f[next][p - node], f[curr][u - node] + (idx != i));
                    }
                }
                curr ^= 1;
                next ^= 1;
                memset(f[next], 0x3f, sizeof f[next]);
            }

            int ans = INF;
            for (Tnode *u = root; u != nodetail; u++) {
                ans = MIN(ans, f[curr][u - node]);
            }
            return ans == INF ? -1 : ans;
        }
} ac;

char s[1024];

int main()
{
    gene['A'] = 0;
    gene['T'] = 1;
    gene['G'] = 2;
    gene['C'] = 3;

    int n, task = 1;
    while (scanf("%d", &n), n) {
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build_fail();

        scanf("%s", s);
        int r = ac.query(s);
        printf("Case %d: %d\n", task++, r);
    }

    return 0;
}

