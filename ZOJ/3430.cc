/*
 *  SRC: ZOJ 3430
 * PROB: Detect the Virus
 * ALGO: AC Automaton
 * DATE: Aug 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <set>

using namespace std;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[256];
            Tnode *fail;
            int id;

            Tnode() : fail(0), id(0) { memset(next, 0, sizeof next); }
        };
        Tnode *root;

    public:
        void build() { root = new Tnode(); }

        void insert(int *s, int id)
        {
            Tnode *p = root;
            while (*s != -1) {
                if (!p->next[*s]) p->next[*s] = new Tnode();
                p = p->next[*s++];
            }
            p->id = id;
        }

        void build_fail()
        {
            queue<Tnode *> que;
            for (int i = 0; i < 256; i++) {
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
                for (int i = 0; i < 256; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        que.push(u->next[i]);
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        int query(int *s)
        {
            set<int> virus;
            Tnode *p = root;
            while (*s != -1) {
                p = p->next[*s++];
                for (Tnode *t = p; t != root; t = t->fail) {
                    if (t->id) virus.insert(t->id);
                }
            }
            return virus.size();
        }
} ac;

const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int base64[256];
char strbuf[65536];
int code[65536];

void decode(const char *s, int *code)
{
    while (*s) {
        *code++ = (base64[s[0]] << 2) | (base64[s[1]] >> 4);
        if (s[2] == '=') break;
        *code++ = ((base64[s[1]] & 0x0f) << 4) | (base64[s[2]] >> 2);
        if (s[3] == '=') break;
        *code++ = ((base64[s[2]] & 0x03) << 6) | base64[s[3]];
        s += 4;
    }
    *code = -1;
}

int main()
{
    for (int i = 0; i < 64; i++) {
        base64[cb64[i]] = i;
    }

    int n;
    while (~scanf("%d", &n)) {
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            decode(strbuf, code);
            ac.insert(code, i + 1);
        }
        ac.build_fail();

        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%s", strbuf);
            decode(strbuf, code);
            int r = ac.query(code);
            printf("%d\n", r);
        }

        putchar(10);
    }

    return 0;
}

