/*
 *  SRC: ZOJ 3228
 * PROB: Searching the String
 * ALGO: AC Automaton
 * DATE: Sep 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <map>

using namespace std;

const int MAXN = 1e5 + 10;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;
            int id;
        };
        Tnode node[6 * MAXN];
        Tnode *root, *nodetail;
        int id;

    public:
        int len[MAXN], overlap[MAXN], noverelap[MAXN];
        char *last[MAXN];

        void build()
        {
            memset(overlap, 0, sizeof overlap);
            memset(noverelap, 0, sizeof noverelap);
            memset(last, 0, sizeof last);
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
            id = 1;
        }

        void insert(char *s, int type, int **cnt)
        {
            Tnode *p = root;
            char *t = s;
            while (*s) {
                int idx = *s++ - 'a';
                if (!p->next[idx]) p->next[idx] = nodetail++;
                p = p->next[idx];
            }
            if (!p->id) p->id = id++;
            len[p->id] = s - t;
            if (type) *cnt = &noverelap[p->id];
            else *cnt = &overlap[p->id];
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

        void query(char *s)
        {
            Tnode *p = root;
            while (*s) {
                int idx = *s++ - 'a';
                p = p->next[idx];
                for (Tnode *t = p; t != root; t = t->fail) {
                    if (t->id) {
                        if (last[t->id] == 0 || s - last[t->id] >= len[t->id]) {
                            noverelap[t->id]++;
                            last[t->id] = s;
                        }
                        overlap[t->id]++;
                    }
                }
            }
        }
} ac;

struct Query {
    char s[10];
    int type;
} query[MAXN];

int *cnt[MAXN];
char A[MAXN];

int main()
{
    int task = 1;
    while (~scanf("%s", A)) {
        int n;
        scanf("%d", &n);
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%d%s", &query[i].type, query[i].s);
            ac.insert(query[i].s, query[i].type, &cnt[i]);
        }
        ac.build_fail();
        ac.query(A);

        printf("Case %d\n", task++);
        for (int i = 0; i < n; i++) {
            printf("%d\n", *cnt[i]);
        }
        putchar(10);
    }


    return 0;
}

