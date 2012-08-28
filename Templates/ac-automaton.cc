/*
 *  SRC: POJ 1204
 * PROB: Word Puzzles
 * ALGO: AC Automaton
 * DATE: Jul 23, 2011
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

int l, c, w, ans_cnt, len[1010];
char map[1010][1010], word[1010];

struct Answers {
    int x, y;
    char dir;
} ans[1010];

class ACAutomaton {
    private:
        const static int CHARSET_SIZE = 26;
        const static int NODE_MAX_SIZE = 200000;

        struct Tnode {
            Tnode *next[CHARSET_SIZE];
            Tnode *fail;
            int exist;
            int id;
        };
        Tnode node[NODE_MAX_SIZE];
        Tnode *node_tail;
        Tnode *root;

    public:
        ACAutomaton() { reset(); }

        void reset()
        {
            memset(node, 0, sizeof(node));
            node_tail = node;
            root = node_tail++;
        }

        int insert(char *s, int id)
        {
            Tnode *p = root;

            while (*s) {
                int idx = *s++ - 'A';
                if (!p->next[idx]) p->next[idx] = node_tail++;
                p = p->next[idx];
            }

            p->exist++;
            p->id = id;

            return true;
        }

        void build_fail()
        {
            queue<Tnode *> Q;

            for (int i = 0; i < CHARSET_SIZE; i++) {
                if (root->next[i]) {
                    root->next[i]->fail = root;
                    Q.push(root->next[i]);
                } else {
                    root->next[i] = root;
                }
            }

            while (!Q.empty()) {
                Tnode *curr = Q.front();
                Q.pop();

                for (int i = 0; i < CHARSET_SIZE; i++) {
                    if (curr->next[i]) {
                        curr->next[i]->fail = curr->fail->next[i];
                        Q.push(curr->next[i]);
                    } else {
                        curr->next[i] = curr->fail->next[i];
                    }
                }

                // for nesting case
                // if (!curr->id) curr->id = curr->fail->id;
            }
        }

//        int query(char* s)
        void query(int x, int y, int dx, int dy, char dir)
        {
//            int res = 0;

            Tnode *p = root;
            while (map[x][y]) {
                int idx = map[x][y] - 'A';
                p = p->next[idx];

                if (p->id) {
                    Tnode *t = p;
                    while (t != root && t->id != -1) {
                        if (t->id) {
                            ans_cnt++;
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

ACAutomaton ac;

int main()
{
    scanf("%d%d%d", &l, &c, &w);

    for (int i = 1; i <= l; i++) scanf("%s", map[i] + 1);

    for (int i = 1; i <= w; i++) {
        scanf("%s", word);
        ac.insert(word, i);
        len[i] = strlen(word);
    }

    ac.build_fail();

    for (int j = 1; j <= c; j++) {
        ac.query(l, j, -1, 0, 'A');
        if (ans_cnt == w) break;

        ac.query(l, j, -1, 1, 'B');
        if (ans_cnt == w) break;

        ac.query(1, j, 1, 1, 'D');
        if (ans_cnt == w) break;

        ac.query(1, j, 1, 0, 'E');
        if (ans_cnt == w) break;

        ac.query(1, j, 1, -1, 'F');
        if (ans_cnt == w) break;

        ac.query(l, j, -1, -1, 'H');
        if (ans_cnt == w) break;
    }

    for (int i = 1; i <= l; i++) {
        if (ans_cnt == w) break;

        ac.query(i, 1, -1, 1, 'B');
        if (ans_cnt == w) break;

        ac.query(i, 1, 0, 1, 'C');
        if (ans_cnt == w) break;

        ac.query(i, 1, 1, 1, 'D');
        if (ans_cnt == w) break;

        ac.query(i, c, 1, -1, 'F');
        if (ans_cnt == w) break;

        ac.query(i, c, 0, -1, 'G');
        if (ans_cnt == w) break;

        ac.query(i, c, -1, -1, 'H');
        if (ans_cnt == w) break;
    }

    for (int i = 1; i <= w; i++)
        printf("%d %d %c\n", ans[i].x - 1, ans[i].y - 1, ans[i].dir);

    return 0;
}
