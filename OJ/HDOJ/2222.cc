/*
 *  SRC: HDOJ 2222
 * PROB: Keywords Search
 * ALGO: AC Automaton
 * DATE: Aug 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;
            int exist;

            Tnode() : fail(0), exist(0) { memset(next, 0, sizeof next); }
        };
        Tnode *root;

    public:
        void build()
        {
            root = new Tnode();
        }

        void insert(char *s)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - 'a']) p->next[*s - 'a'] = new Tnode();
                p = p->next[*s++ - 'a'];
            }
            p->exist++;
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

        int query(char *s)
        {
            int cnt = 0;
            Tnode *p = root;
            while (*s) {
                p = p->next[*s++ - 'a'];
                if (p->exist) {
                    Tnode *t = p;
                    while (t != root) {
                        if (t->exist) {
                            cnt += t->exist;
                            t->exist = 0;
                        }
                        t = t->fail;
                    }
                }
            }

            return cnt;
        }
} ac;

char strbuf[1000010];

int main()
{
    int tasks;
    scanf("%d", &tasks);

    while (tasks--) {
        ac.build();

        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            ac.insert(strbuf);
        }
        ac.build_fail();

        scanf("%s", strbuf);
        int r = ac.query(strbuf);
        printf("%d\n", r);
    }

    return 0;
}

