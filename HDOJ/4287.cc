/*
 *  SRC: HDOJ 4287
 * PROB: Intelligent IME
 * ALGO: Trie
 * DATE: Sep 09, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

int digit[256];

class Trie {
    private:
        struct Tnode {
            Tnode *next[10];
            int cnt;
        } node[30010];
        Tnode *root, *nodetail;

    public:
        void build()
        {
            memset(node, 0, sizeof node);
            nodetail = node;
            root = nodetail++;
        }

        void insert(char *s)
        {
            Tnode *p = root;
            while (*s) {
                int idx = digit[(int)*s++];
                if (!p->next[idx]) p->next[idx] = nodetail++;
                p = p->next[idx];
            }
            p->cnt++;
        }

        int query(char *s)
        {
            Tnode *p = root;
            while (*s) {
                if (!p->next[*s - '0']) return 0;
                p = p->next[*s++ - '0'];
            }
            return p->cnt;
        }
} trie;

char qu[5010][100];
char str[100];

int main()
{
    digit['a'] = digit['b'] = digit['c'] = 2;
    digit['d'] = digit['e'] = digit['f'] = 3;
    digit['g'] = digit['h'] = digit['i'] = 4;
    digit['j'] = digit['k'] = digit['l'] = 5;
    digit['m'] = digit['n'] = digit['o'] = 6;
    digit['p'] = digit['q'] = digit['r'] = digit['s'] = 7;
    digit['t'] = digit['u'] = digit['v'] = 8;
    digit['w'] = digit['x'] = digit['y'] = digit['z'] = 9;

    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n, m;
        scanf("%d%d", &n, &m);

        trie.build();
        for (int i = 0; i < n; i++) {
            scanf("%s", qu[i]);
        }

        for (int i = 0; i < m; i++) {
            scanf("%s", str);
            trie.insert(str);
        }

        for (int i = 0; i < n; i++) {
            int r = trie.query(qu[i]);
            printf("%d\n", r);
        }
    }

    return 0;
}

