/*
 *  SRC: HDOJ 2296
 * PROB: Ring
 * ALGO: AC Automaton
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using std::queue;
using std::reverse;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;
            int val;
        };
        Tnode node[1024];
        Tnode *root, *nodetail;

        struct State {
            int val;
            char c;
            State *prev;
        };
        State f[51][1024];

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
        }

        void insert(char *s, int val)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - 'a']) p->next[*s - 'a'] = nodetail++;
                p = p->next[*s++ - 'a'];
            }
            p->val = val;
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
                u->val += u->fail->val;
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

        void query(int n, char *t)
        {
            State ans;
            memset(f, 0xff, sizeof f);
            f[0][0].val = 0;
            f[0][0].prev = 0;
            ans = f[0][0];
            for (int i = 0; i < n; i++) {
                for (Tnode *u = root; u != nodetail; u++) {
                    if (f[i][u - node].val == -1) continue;
                    for (int j = 0; j < 26; j++) {
                        Tnode *p = u->next[j];
                        if (f[i][u - node].val + p->val > f[i + 1][p - node].val) {
                            f[i + 1][p - node].val = f[i][u - node].val + p->val;
                            f[i + 1][p - node].c = 'a' + j;
                            f[i + 1][p - node].prev = &f[i][u - node];

                            if (f[i + 1][p - node].val > ans.val) ans = f[i + 1][p - node];
                        }
                    }
                }
            }

            char *s = t;
            for (State *p = &ans; p != 0; p = p->prev) {
                *s++ = p->c;
            }
            *--s = '\0';
            reverse(t, s);
        }
} ac;

char word[110][20];
char ans[100];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%s", word[i]);
        }

        ac.build();
        for (int i = 0; i < m; i++) {
            int val;
            scanf("%d", &val);
            ac.insert(word[i], val);
        }
        ac.build_fail();

        ac.query(n, ans);
        puts(ans);
    }

    return 0;
}

