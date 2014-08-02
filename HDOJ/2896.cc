/*
 *  SRC: HDOJ 2896
 * PROB: 病毒侵袭
 * ALGO: AC Automaton
 * DATE: Aug 28, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[128];
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
                if (!p->next[*s]) p->next[*s] = new Tnode();
                p = p->next[*s++];
            }
            p->id = id;
        }

        void build_fail()
        {
            queue<Tnode *> que;
            for (int i = 0; i < 128; i++) {
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
                for (int i = 0; i < 128; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        que.push(u->next[i]);
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        void query(char *s, vector<int> &virus)
        {
            virus.clear();

            Tnode *p = root;
            while (*s) {
                p = p->next[*s++];
                if (p->id) virus.push_back(p->id);
            }
        }
} ac;

char strbuf[10010];

int main()
{
    int n;
    while (~scanf("%d", &n)) {
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            ac.insert(strbuf, i + 1);
        }
        ac.build_fail();

        int m, cnt = 0;
        scanf("%d", &m);
        vector<int> virus;
        for (int i = 0; i < m; i++) {
            scanf("%s", strbuf);
            ac.query(strbuf, virus);
            if (!virus.empty()) {
                cnt++;
                sort(virus.begin(), virus.end());
                printf("web %d:", i + 1);
                for (int j = 0; j < (int)virus.size(); j++) {
                    printf(" %d", virus[j]);
                }
                putchar(10);
            }
        }
        printf("total: %d\n", cnt);
    }

    return 0;
}

