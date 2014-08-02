/*
 *  SRC: HDOJ 3341
 * PROB: Lost's revenge
 * ALGO: AC Automaton
 * DATE: Sep 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

inline int max(int x, int y) { return x > y ? x : y; }

int gene[256];

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[4];
            Tnode *fail;
            int cnt;
        } node[510];
        Tnode *root, *nodetail;
        Tnode *que[510];

        int c0, c1, c2;
        int f[11 * 11 * 11 * 11][510];

        int getidx(int a, int c, int g, int t) { return a + c * c0 + g * c1 + t * c2; }

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
            memset(f, 0xff, sizeof f);
        }

        void insert(char *s)
        {
            Tnode *p = root;
            while (*s) {
                int idx = gene[(int)*s++];
                if (!p->next[idx]) p->next[idx] = nodetail++;
                p = p->next[idx];
            }
            p->cnt++;
        }

        void build_fail()
        {
            Tnode **head = que, **tail = que;
            for (int i = 0; i < 4; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    *tail++ = root->next[i];
                } else {
                    root->next[i] = root;
                }
            }

            while (head != tail) {
                Tnode *u = *head++;
                u->cnt += u->fail->cnt;
                for (int i = 0; i < 4; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        *tail++ = u->next[i];
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        int query(int acnt, int ccnt, int gcnt, int tcnt)
        {
            c0 = acnt + 1;
            c1 = c0 * (ccnt + 1);
            c2 = c1 * (gcnt + 1);

            f[0][0] = 0;
            for (int a = 0; a <= acnt; a++) {
                for (int c = 0; c <= ccnt; c++) {
                    for (int g = 0; g <= gcnt; g++) {
                        for (int t = 0; t <= tcnt; t++) {
                            for (Tnode *u = root; u != nodetail; u++) {
                                if (f[getidx(a, c, g, t)][u - node] == -1) continue;
                                for (int i = 0; i < 4; i++) {
                                    int an = a + (i == 0);
                                    int cn = c + (i == 1);
                                    int gn = g + (i == 2);
                                    int tn = t + (i == 3);
                                    if (an > acnt || cn > ccnt || gn > gcnt || tn > tcnt) continue;
                                    Tnode *p = u->next[i];
                                    f[getidx(an, cn, gn, tn)][p - node] = max(f[getidx(an, cn, gn, tn)][p - node], f[getidx(a, c, g, t)][u - node] + p->cnt);
                                }
                            }
                        }
                    }
                }
            }

            int ans = 0;
            for (Tnode *u = root; u != nodetail; u++) {
                ans = max(ans, f[getidx(acnt, ccnt, gcnt, tcnt)][u - node]);
            }
            return ans;
        }
} ac;

char strbuf[100];
int cnt[256];

int main()
{
    gene['A'] = 0;
    gene['C'] = 1;
    gene['G'] = 2;
    gene['T'] = 3;

    int task = 1;
    int n;
    while (scanf("%d", &n), n) {
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            ac.insert(strbuf);
        }
        ac.build_fail();

        scanf("%s", strbuf);
        cnt['A'] = cnt['C'] = cnt['G'] = cnt['T'] = 0;
        for (char *t = strbuf; *t; t++) {
            cnt[(int)*t]++;
        }
        int r = ac.query(cnt['A'], cnt['C'], cnt['G'], cnt['T']);
        printf("Case %d: %d\n", task++, r);
    }

    return 0;
}

