/*
 *  SRC: HDOJ 2825
 * PROB: Wireless Password
 * ALGO: AC Automaton
 * DATE: Aug 31, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

const int INF = 0x3f3f3f3f;
const int MOD = 20090717;

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[26];
            Tnode *fail;

            int tag;
        };
        Tnode node[110];
        Tnode *root, *nodetail;

        int f[2][110][1024];

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
        }

        void insert(char *s, int idx)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - 'a']) p->next[*s - 'a'] = nodetail++;
                p = p->next[*s++ - 'a'];
            }
            p->tag |= 1 << idx;
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
                u->tag |= u->fail->tag;
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

        int query(int n, int m, int K)
        {
            memset(f, 0x3f, sizeof f);
            f[0][0][0] = 1;
            int curr = 0, next = 1;
            for (int i = 1; i <= n; i++) {
                for (Tnode *u = root; u != nodetail; u++) {
                    for (int j = 0; j < 1 << m; j++) {
                        if (f[curr][u - node][j] == INF) continue;
                        for (int k = 0; k < 26; k++) {
                            Tnode *p = u->next[k];
                            int tag = j | p->tag;
                            if (f[next][p - node][tag] == INF) f[next][p - node][tag] = 0;
                            f[next][p - node][tag] = (f[next][p - node][tag] + f[curr][u - node][j]) % MOD;
                        }
                    }
                }
                curr ^= 1;
                next ^= 1;
                memset(f[next], 0x3f, sizeof f[next]);
            }

            int res = 0;
            for (Tnode *u = root; u != nodetail; u++) {
                for (int j = 0; j < 1 << m; j++) {
                    if (f[curr][u - node][j] == INF) continue;
                    int cnt = 0;
                    for (int k = 0; k < 32; k++) {
                        if (j & (1 << k)) cnt++;
                    }
                    if (cnt >= K) res = (res + f[curr][u - node][j]) % MOD;
                }
            }

            return res;
        }
} ac;

int main()
{
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k), n || m || k) {
        ac.build();
        for (int i = 0; i < m; i++) {
            char s[20];
            scanf("%s", s);
            ac.insert(s, i);
        }
        ac.build_fail();
        int r = ac.query(n, m, k);
        printf("%d\n", r);
    }

    return 0;
}

