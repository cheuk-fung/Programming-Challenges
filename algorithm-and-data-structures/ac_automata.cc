/*
 *  SRC: POJ 1204
 * PROB: Word Puzzles
 * ALGO: AC Automata
 * DATE: Jul 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

int l, c, w, ansCnt, len[1010];
char map[1010][1010], word[1010];

struct Answers {
    int x, y;
    char dir;
} ans[1010];

class ACAutomata {
    private:
        const static int CHARSET_SIZE = 26;
        const static int BUF_SIZE = 200000;

        struct Node {
            Node* next[CHARSET_SIZE];
            Node* fail;
            int exist;
            int id; // used just in this problem
        };
        Node* root;

        int bufansCnt;
        Node buf[BUF_SIZE];

    public:
        void reset()
        {
            bufansCnt = 0;
            root = &buf[bufansCnt++];
            memset(root->next, 0, sizeof(root->next));
            root->fail = 0;
            root->exist = false;
        }

//        int insert(char*s)
        int insert(char *s, int id)
        {
            Node* p = root;

            while (*s) {
                int index = *s - 'A';
                if (!p->next[index]) {
                    p->next[index] = &buf[bufansCnt++];
/*
 *                     memset(p->next[index]->next, 0, sizeof(root->next));
 *                     p->fail = 0;
 *                     p->next[index]->exist = 0;
 */
                }
                p = p->next[index];
                s++;
            }

            p->exist++;
            p->id = id;

            return true;
        }

        void buildFail()
        {
            queue<Node*> Q;

            for (int i = 0; i < CHARSET_SIZE; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    Q.push(root->next[i]);
                }
                else root->next[i] = root;
            }

            while (!Q.empty()) {
                Node* curr = Q.front();
                Q.pop();

                for (int i = 0; i < CHARSET_SIZE; i++) {
                    Node* u = curr->next[i];
                    if (u) {
                        Node* v = curr->fail;
                        while (!v->next[i]) v = v->fail;
                        u->fail = v->next[i];

                        Q.push(u);
                    }
                }
            }
        }

//        int query(char* s)
        void query(int x, int y, int dx, int dy, char dir)
        {
//            int res = 0;

            Node* p = root;
            while (map[x][y]) {
                int index = map[x][y] - 'A';
                while (!p->next[index] && p != root) p = p->fail;
                p = p->next[index];

                if (p->id) {
                    Node* t = p;
                    while (t != root && t->id != -1) {
                        if (t->id) {
                            ansCnt++;
                            ans[t->id].x = x - (len[t->id] -1) * dx;
                            ans[t->id].y = y - (len[t->id] -1) * dy;
                            ans[t->id].dir = dir;
                        }
                        t->id = -1;
                        t = t->fail;
                    }
                }

                x += dx;
                y += dy;
            }

//            return res;
        }
};

ACAutomata aca;

int main()
{
    aca.reset();

    scanf("%d%d%d", &l, &c, &w);

    for (int i = 1; i <= l; i++) scanf("%s", map[i] + 1);

    for (int i = 1; i <= w; i++) {
        scanf("%s", word);
        aca.insert(word, i);
        len[i] = strlen(word);
    }

    aca.buildFail();

    for (int j = 1; j <= c; j++) {
        aca.query(l, j, -1, 0, 'A');
        if (ansCnt == w) break;

        aca.query(l, j, -1, 1, 'B');
        if (ansCnt == w) break;

        aca.query(1, j, 1, 1, 'D');
        if (ansCnt == w) break;

        aca.query(1, j, 1, 0, 'E');
        if (ansCnt == w) break;
        
        aca.query(1, j, 1, -1, 'F');
        if (ansCnt == w) break;

        aca.query(l, j, -1, -1, 'H');
        if (ansCnt == w) break;
    }

    for (int i = 1; i <= l; i++) {
        if (ansCnt == w) break;

        aca.query(i, 1, -1, 1, 'B');
        if (ansCnt == w) break;

        aca.query(i, 1, 0, 1, 'C');
        if (ansCnt == w) break;

        aca.query(i, 1, 1, 1, 'D');
        if (ansCnt == w) break;

        aca.query(i, c, 1, -1, 'F');
        if (ansCnt == w) break;

        aca.query(i, c, 0, -1, 'G');
        if (ansCnt == w) break;

        aca.query(i, c, -1, -1, 'H');
        if (ansCnt == w) break;
    }

    for (int i = 1; i <= w; i++)
        printf("%d %d %c\n", ans[i].x - 1, ans[i].y - 1, ans[i].dir);

    return 0;
}
