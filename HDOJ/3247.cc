/*
 *  SRC: HDOJ 3247
 * PROB: Resource Archiver
 * ALGO: AC Automaton
 * DATE: Sep 02, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

class AC_Automaton {
    private:
        struct Tnode {
            Tnode *next[2];
            Tnode *fail;
            short tag;
        } node[60010];
        Tnode *root, *nodetail;
        Tnode *que[60010];

        static const int QUESIZE = 1000000;
        struct State {
            int s;
            int l;
        } sque[QUESIZE];
        bool vis[60010][1024];

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
            memset(vis, 0, sizeof vis);
        }

        void insert(char *s, int id)
        {
            Tnode *p = root;
            while (*s) {
                int idx = *s++ - '0';
                if (!p->next[idx]) p->next[idx] = nodetail++;
                p = p->next[idx];
            }
            if (id >= 0) p->tag = 1 << id;
            else p->tag = -1;
        }

        void build_fail()
        {
            Tnode **head = que, **tail = que;
            for (int i = 0; i < 2; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    *tail++ = root->next[i];
                } else {
                    root->next[i] = root;
                }
            }

            while (head != tail) {
                Tnode *u = *head++;
                if (u->tag >= 0 && u->fail->tag >= 0) u->tag |= u->fail->tag;
                else u->tag = -1;
                for (int i = 0; i < 2; i++) {
                    if (u->next[i]) {
                        u->next[i]->fail = u->fail->next[i];
                        *tail++ = u->next[i];
                    } else {
                        u->next[i] = u->fail->next[i];
                    }
                }
            }
        }

        int query(int n)
        {
            int head = 0, tail = 0;
            sque[tail++] = (State){0, 0};
            vis[0][0] = true;
            while (head != tail) {
                State now = sque[head];
                head = (head + 1) % QUESIZE;

                int idx = now.s >> n, tag = now.s & ((1 << n) - 1);
                int len = now.l;
                for (int i = 0; i < 2; i++) {
                    Tnode *p = node[idx].next[i];
                    if (p->tag < 0) continue;
                    int nidx = p - node;
                    int ntag = tag | p->tag;
                    if (ntag == (1 << n) - 1) return len + 1;
                    if (vis[nidx][ntag]) continue;
                    sque[tail] = (State){(nidx << n) | ntag, len + 1};
                    tail = (tail + 1) % QUESIZE;
                    vis[nidx][ntag] = true;
                }
            }

            return 0;
        }
} ac;

char strbuf[50010];

int main()
{
    //printf("%d\n", sizeof ac / 1024);

    int n, m;
    while (scanf("%d%d", &n, &m), n || m) {
        ac.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", strbuf);
            ac.insert(strbuf, i);
        }
        for (int i = 0; i < m; i++) {
            scanf("%s", strbuf);
            ac.insert(strbuf, -1);
        }
        ac.build_fail();

        int r = ac.query(n);
        printf("%d\n", r);
    }

    return 0;
}

