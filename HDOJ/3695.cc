/*
 *  SRC: HDOJ 3695
 * PROB: Computer Virus on Planet Pandora
 * ALGO: AC Automata
 * DATE: Oct 06, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>

using std::queue;
using std::swap;

bool vis[256];

class ACAutomata {
    private:
        const static int CHARSET_SIZE = 26;
        const static int NODE_MAX_SIZE = 500000;

        struct Tnode {
            Tnode* next[CHARSET_SIZE];
            Tnode* fail;
            int id, id2;
        };
        Tnode* root;

        int node_cnt;
        Tnode node[NODE_MAX_SIZE];

    public:
        ACAutomata() { reset(); }

        void reset()
        {
            memset(node, 0, sizeof(node));
            node_cnt = 0;
            root = &node[node_cnt++];
        }

        int insert(char *s, int id)
        {
            Tnode* p = root;

            while (*s) {
                int idx = *s - 'A';
                if (!p->next[idx])
                    p->next[idx] = &node[node_cnt++];
                p = p->next[idx];
                s++;
            }

            if (p->id) p->id2 = id;
            else p->id = id;

            return true;
        }

        void build_fail()
        {
            queue<Tnode*> Q;

            for (int i = 0; i < CHARSET_SIZE; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    Q.push(root->next[i]);
                }
                else root->next[i] = root;
            }

            while (!Q.empty()) {
                Tnode* curr = Q.front();
                Q.pop();

                for (int i = 0; i < CHARSET_SIZE; i++) {
                    Tnode* u = curr->next[i];
                    if (u) {
                        Tnode* v = curr->fail;
                        while (!v->next[i]) v = v->fail;
                        u->fail = v->next[i];

                        Q.push(u);
                    }
                }
                
                if (!curr->id) curr->id = curr->fail->id;
            }
        }

        Tnode* solve(char c, Tnode *p)
        {
            int idx = c - 'A';
            while (!p->next[idx] && p != root) p = p->fail;
            p = p->next[idx];

            if (p->id) {
                Tnode *t = p;
                while (t != root && t->id) {
                    vis[t->id] = 1;
                    vis[t->id2] = 1;
                    t = t->fail;
                }
            }

            return p;
        }

        int query(char* s, int n)
        {
            memset(vis, 0, sizeof(vis));

            Tnode *curr = root;
            while (*s) {
                if (*s != '[') {
                    curr = solve(*s++, curr);
                    continue;
                }

                s++;
                int num = 0;
                while (isdigit(*s)) num = num * 10 + *s++ - '0';
                if (num > 1000) num = 1000;
                for (int i = 0; i < num; i++)
                    curr = solve(*s, curr);
                s += 2;
            }

            int cnt = 0;
            for (int i = 1; i <= n; i++)
                if (vis[i]) cnt++;

            return cnt;
        }
};

ACAutomata aca;

int n;
char virus[1024], program[5200000];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", virus);
            aca.insert(virus, i + 1);

            for (int j = 0, k = strlen(virus) - 1; j < k; j++, k--)
                swap(virus[j], virus[k]);
            aca.insert(virus, i + 1);
        }
        scanf("%s", program);

        aca.build_fail();
        printf("%d\n", aca.query(program, n));
        aca.reset();
    }

    return 0;
}
