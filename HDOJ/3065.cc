/*
 *  SRC: HDOJ 3065
 * PROB: 病毒侵袭持续中
 * ALGO: AC Automaton
 * DATE: Aug 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>

using namespace std;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;
            int id;

            Tnode() : fail(0), id(0) { memset(next, 0, sizeof next); }
        };
        Tnode *root;

    public:
        void build() { root = new Tnode(); }

        void insert(char *s, int id)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - 'A']) p->next[*s - 'A'] = new Tnode();
                p = p->next[*s++ - 'A'];
            }
            p->id = id;
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

        void query(char *s, int *cnt)
        {
            Tnode *p = root;
            while (*s) {
                if (!isupper(*s)) {
                    s++;
                    p = root;
                    continue;
                }

                p = p->next[*s++ - 'A'];
                Tnode *t = p;
                while (t != root) {
                    if (t->id) cnt[t->id]++;
                    t = t->fail;
                }
            }
        }
} ac;

char strbuf[2000010];
char virus[1010][55];
int cnt[1010];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ac.build();
        for (int i = 1; i <= n; i++) {
            scanf("%s", virus[i]);
            ac.insert(virus[i], i);
        }
        ac.build_fail();

        scanf("%s", strbuf);
        memset(cnt, 0, sizeof cnt);
        ac.query(strbuf, cnt);
        for (int i = 1; i <= n; i++) {
            if (cnt[i]) printf("%s: %d\n", virus[i], cnt[i]);
        }
    }

    return 0;
}

