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

struct Node {
    Node* next[10];
    bool exist;

/*
 *     Node() : isEnd(false)
 *     {
 *         memset(next, 0, sizeof(next));
 *     }
 */
};
Node* Trie;
Node buf[200000];
int TrieCnt;

bool TrieInsert(Node* p, char* s)
{
    if (p->exist) return false;

    if (*s == '\0') {
        p->exist = true;
        return true;
    }

//    if (!p->next[*s - '0']) p->next[*s - '0'] = new Node;
    if (!p->next[*s - '0']) {
        p->next[*s - '0'] = &buf[++TrieCnt];
        memset(p->next[*s - '0']->next, 0, sizeof(Trie->next));
        p->next[*s -'0']->exist = false;
    }
    return TrieInsert(p->next[*s - '0'], s + 1);
}

int n;
char phone[10000][20];

int cmp(const void* a, const void* b)
{
    return strcmp((char*)a, (char*)b);
}

void work()
{
    TrieCnt = 0;
    Trie = &buf[0];
    memset(Trie->next, 0, sizeof(Trie->next));
    Trie->exist = false;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%s", phone[i]);

    qsort(phone, n, sizeof(char) * 20, cmp);

    for (int i = 0; i < n; i++)
        if (!TrieInsert(Trie, phone[i])) {
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
