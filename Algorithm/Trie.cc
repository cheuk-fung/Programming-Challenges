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

class Trie
{
    private:
        struct Node {
            Node* next[10];
            bool exist;
        };
        Node* root;

        int cnt;
        Node buf[200000]; // change it to adapt to need

        bool _insert(Node* p, char* s)
        {
            if (p->exist) return false;

            if (*s == '\0') {
                p->exist = true;
                return true;
            }

            if (!p->next[*s - '0']) {
                p->next[*s - '0'] = &buf[cnt++];
                memset(p->next[*s - '0']->next, 0, sizeof(root->next));
                p->next[*s -'0']->exist = false;
            }
            return _insert(p->next[*s - '0'], s + 1);
        }

    public:
        void reset()
        {
            cnt = 0;
            root = &buf[cnt++];
            memset(root->next, 0, sizeof(root->next));
            root->exist = false;
        }

        bool insert(char *s)
        {
            return _insert(root, s);
        }
};

Trie trie;

int n;
char phone[10000][20];

int cmp(const void* a, const void* b)
{
    return strcmp((char*)a, (char*)b);
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
