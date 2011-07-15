/*
 *  SRC: POJ 1077
 * PROB: Eight
 * ALGO: BFS
 * DATE: Jul 15, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

const int fac[] = {40320, 5040, 720, 120, 24, 6, 2, 1, 1};

struct Node {
    bool v;
    int pre;
    char c;

    Node() { }
    Node(int _v, int _pre, char _c)
        : v(_v), pre(_pre), c(_c)
    { }
};

queue<int> Q;
Node visited[370000];
bool used[9];

int start, final;

int encode(const char* s)
{
    memset(used, false, sizeof(used));

    int r = 0;
    for (int i = 0; i < 9; i++) {
        int sum = s[i] - '0';
        int cnt = 0;
        for (int j = 0; j < sum; j++)
            if (!used[j]) cnt++;

        r += cnt * fac[i];
        used[sum] = true;
    }

    return r;
}

char* decode(int code, char* s)
{
    memset(used, false, sizeof(used));

    for (int i = 0; i < 9; i++) {
        int sum = code / fac[i];
        code %= fac[i];

        int cnt = 0, j = 0;
        while (cnt < sum || used[j]) {
            if (!used[j]) cnt++;
            j++;
        }
        used[j] = true;
        s[i] = j + '0';
    }
    s[9] = '\0';

    return s;
}

void printRoute(int id)
{
    if (visited[id].pre == -1) return ;
    printRoute(visited[id].pre);
    putchar(visited[id].c);
}

bool swap(const char* s, int id, int p, int q, char c)
{
    char t[10];
    strcpy(t, s);
    t[p] = t[q];
    t[q] = '0';

    int newId = encode(t);

    if (!visited[newId].v) {
        Q.push(newId);
        visited[newId] = Node(true, id, c);
    }

    if (newId == final) {
        printRoute(newId);
        putchar(10);

        return true;
    }

    return false;
}

void bfs()
{
    Q.push(start);
    visited[start] = Node(true, -1, 0);

    while (!Q.empty()) {
        int id = Q.front();
        Q.pop();

        char s[10];
        decode(id, s);

        int pos = 0;
        while (s[pos] != '0') pos++;

        if (pos % 3 != 2)
            if (swap(s, id, pos, pos + 1, 'r')) return ;
        if (pos % 3 != 0)
            if (swap(s, id, pos, pos - 1, 'l')) return ;
        if (pos > 2)
            if (swap(s, id, pos, pos - 3, 'u')) return ;
        if (pos < 6)
            if (swap(s, id, pos, pos + 3, 'd')) return ;
    }

    puts("unsolvable");
}

int main()
{
    char t[10];
    t[9] = '\0';
    for (int i = 0; i < 9; i++) {
        char c;
        while ((c = getchar()) == ' ') ;
        if (c == 'x') t[i] = '0';
        else t[i] = c;
    }

    start = encode(t);
    final = encode("123456780");
        
    bfs();

    return 0;
}
