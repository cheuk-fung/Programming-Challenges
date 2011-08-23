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
        const static int BUF_SIZE = 200000;

        struct Node {
            Node* next[CHARSET_SIZE];
            int exist;
        };
        Node* root;

        int bufCnt;
        Node buf[BUF_SIZE];

    public:
        void reset()
        {
            bufCnt = 0;
            root = &buf[bufCnt++];
            memset(root->next, 0, sizeof(root->next));
            root->exist = false;
        }

        int insert(char *s)
        {
            Node* p = root;

            while (*s) {
                if (p->exist) return false;

                int index = *s - '0';
                if (!p->next[index]) {
                    p->next[index] = &buf[bufCnt++];
                    memset(p->next[index]->next, 0, sizeof(root->next));
                    p->next[index]->exist = 0;
                }
                p = p->next[index];
                s++;
            }

            p->exist++;

            return true;
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
