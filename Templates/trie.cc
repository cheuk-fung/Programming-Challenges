/*
 *  SRC: POJ 3630
 * PROB: Phone List
 * ALGO: Trie
 * DATE: Jul 22, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

class Trie {
    private:
        const static int CHARSET_SIZE = 10;
        const static int NODE_MAX_SIZE = 200000;

        struct Tnode {
            Tnode *next[CHARSET_SIZE];
            int exist;
        };
        Tnode node[NODE_MAX_SIZE],
              *node_tail,
              *root;

    public:
        Trie()
        {
            reset();
        }

        void reset()
        {
            memset(node, 0, sizeof(node));
            node_tail = node;
            root = node_tail++;
            root->exist = false;
        }

        int insert(char *s)
        {
            Tnode *p = root;

            while (*s) {
                int idx = *s++ - '0';
                if (!p->next[idx]) p->next[idx] = node_tail++;
                p = p->next[idx];
                if (p->exist) return false;
            }

            p->exist++;

            return true;
        }
};

Trie trie;

int n;
char phone[10000][20];

int cmp(const void *a, const void *b)
{
    return strcmp((char *)a, (char *)b);
}

void work()
{
    trie.reset();

    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%s", phone[i]);

    qsort(phone, n, sizeof(char) * 20, cmp);

    for (int i = 0; i < n; i++)
        if (!trie.insert(phone[i])) {
            puts("NO");
            return ;
        }

    puts("YES");
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) work();

    return 0;
}
