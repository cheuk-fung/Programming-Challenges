/*
 *  SRC: HDOJ 3689
 * PROB: Infinite monkey theorem
 * ALGO: DP on AC Automata
 * DATE: Nov 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const double eps = 1e-8;

using std::queue;
using std::max;

int n, l;
double w[26];

class ACAutomata {
    private:
        const static int CHARSET_SIZE = 26;
        const static int NODE_MAX_SIZE = 1024;

        struct Tnode {
            Tnode* next[CHARSET_SIZE];
            Tnode* fail;
            int id;
        };
        Tnode* root;

        int node_cnt;
        Tnode node[NODE_MAX_SIZE];

        double f[2][1024];
        bool vis[2][1024];
        int curr, next;

    public:
        ACAutomata() { reset(); }

        void reset()
        {
            memset(node, 0, sizeof(node));
            node_cnt = 0;
            root = &node[node_cnt++];

            for (int i = 0; i < NODE_MAX_SIZE; i++) f[0][i] = f[1][i] = 0.0;
            memset(vis, 0, sizeof(vis));
            curr = 0, next = 1;
        }

        int insert(char *s, int id)
        {
            Tnode* p = root;

            while (*s) {
                int idx = *s - 'a';
                if (!p->next[idx])
                    p->next[idx] = &node[node_cnt++];
                p = p->next[idx];
                s++;
            }

            p->id = id;

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
            }
        }

        void query()
        {
            double ans = 0.0;

            f[curr][0] = 100.0;
            vis[curr][0] = 1;
            for (int i = 0; i < l; i++) {
                for (int j = 0; j < node_cnt; j++)
                    if (vis[curr][j])
                        for (int idx = 0; idx < CHARSET_SIZE; idx++) {
                            Tnode *p = &node[j];
                            while (!p->next[idx] && p != root) p = p->fail;
                            p = p->next[idx];

                            if (p->id) ans += f[curr][j] * w[idx];
                            else {
                                vis[next][p - node] = true;
                                f[next][p - node] += f[curr][j] * w[idx];
                            }
                        }
                curr ^= 1;
                next ^= 1;
                for (int j = 0; j < node_cnt; j++) {
                    f[next][j] = 0.0;
                    vis[next][j] = 0;
                }
            }

            printf("%.2f%%\n", ans + eps);
        }
};

ACAutomata aca;

int main()
{
    char str[100];
    while (scanf("%d%d", &n, &l), n && l) {
        for (int i = 0; i < 26; i++) w[i] = 0.0;

        for (int i = 0; i < n; i++) {
            char c;
            scanf(" %c", &c);
            scanf("%lf", w + (c - 'a'));
        }
        scanf(" %s", str);
        aca.insert(str, 1);

        aca.build_fail();
        aca.query();
        aca.reset();
    }

    return 0;
}
