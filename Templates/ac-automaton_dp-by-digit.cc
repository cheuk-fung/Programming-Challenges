#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

class ACAutomaton {
    private:
        struct Tnode {
            Tnode *next[10];
            Tnode *fail;
            bool tag;
        } tbuf[50];
        Tnode *root, *tail;;

        long long f[50][50];
        long long g[50][50];

    public:
        void build()
        {
            memset(tbuf, 0, sizeof tbuf);
            tail = tbuf;
            root = tail++;
        }

        void insert(const char *s)
        {
            Tnode *p = root;
            while (*s) {
                int id = *s++ - '0';
                if (!p->next[id]) p->next[id] = tail++;
                p = p->next[id];
            }
            p->tag = true;
        }

        void build_fail()
        {
            queue<Tnode *> Q;
            for (int i = 0; i <= 9; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    Q.push(root->next[i]);
                } else {
                    root->next[i] = root;
                }
            }

            while (!Q.empty()) {
                Tnode *u = Q.front();
                Q.pop();
                u->tag |= u->fail->tag;
                for (int i = 0; i <= 9; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        Q.push(u->next[i]);
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        long long query(const char *s) // [0, s)
        {
            long long res = root->next[0]->tag ? 0 : 1;
            int len = strlen(s);

            memset(f, 0, sizeof f);
            f[0][0] = 1;
            for (int i = 0; i < len - 1; i++) {
                for (Tnode *p = root; p != tail; p++) {
                    if (!f[i][p - root]) continue;
                    for (int j = i == 0 ? 1 : 0; j <= 9; j++) {
                        Tnode *q = p->next[j];
                        if (q->tag) continue;
                        f[i + 1][q - root] += f[i][p - root];
                        res += f[i][p - root];
                    }
                }
            }

            memset(f, 0, sizeof f);
            memset(g, 0, sizeof g);
            g[0][0] = 1;
            for (int i = 0; i < len; i++) {
                for (Tnode *p = root; p != tail; p++) {
                    if (f[i][p - root]) {
                        for (int j = i == 0 ? 1 : 0; j <= 9; j++) {
                            Tnode *q = p->next[j];
                            if (q->tag) continue;
                            f[i + 1][q - root] += f[i][p - root];
                        }
                    }
                    if (g[i][p - root]) {
                        for (int j = i == 0 ? 1 : 0; j < s[i] - '0'; j++) {
                            Tnode *q = p->next[j];
                            if (q->tag) continue;
                            f[i + 1][q - root] += g[i][p - root];
                        }
                        Tnode *q = p->next[s[i] - '0'];
                        if (!q->tag) {
                            g[i + 1][q - root] += g[i][p - root];
                        }
                    }
                }
            }
            for (Tnode *p = root; p != tail; p++) {
                res += f[len][p - root];
            }

            return res;
        }
} ac;

char str[50];
char zero[] = "0";

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        long long l, r, a, b;
        scanf("%lld%lld%lld%lld", &l, &r, &a, &b);
        r++;

        ac.build();
        ac.insert(zero);
        sprintf(str, "%lld", a);
        ac.insert(str);
        sprintf(str, "%lld", b);
        ac.insert(str);
        ac.build_fail();

        sprintf(str, "%lld", l);
        long long lret = ac.query(str);
        sprintf(str, "%lld", r);
        long long rret = ac.query(str);

        ac.build();
        ac.insert(zero);
        ac.build_fail();

        sprintf(str, "%lld", l);
        long long zlret = ac.query(str);
        sprintf(str, "%lld", r);
        long long zrret = ac.query(str);

        long long lres = l - lret - (l - zlret);
        long long rres = r - rret - (r - zrret);
        long long res = rres - lres;
        printf("%lld\n", res);
    }

    return 0;
}

