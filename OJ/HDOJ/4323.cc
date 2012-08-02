/*
 *  SRC: HDOJ 4323
 * PROB: Magic Number
 * ALGO: BK-tree
 * DATE: Aug 01, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 2000;
const int MAXLEN = 15;

class BKTree {
    private:
        struct TNode {
            string s;
            TNode *next[MAXLEN + 1];
        };
        TNode nodes[MAXN];
        TNode *node_tail;
        TNode *root;

        int f[MAXLEN + 2][MAXLEN + 2];

        int diff(const string &a, const string &b)
        {
            f[0][0] = 0;
            for (int i = 1; i <= (int)a.length(); i++) f[i][0] = i;
            for (int i = 1; i <= (int)b.length(); i++) f[0][i] = i;
            for (int i = 1; i <= (int)a.length(); i++) {
                for (int j = 1; j <= (int)b.length(); j++) {
                    f[i][j] = min(f[i - 1][j - 1] + (a[i - 1] != b[j - 1]), min(f[i - 1][j], f[i][j - 1]) + 1);
                }
            }
            return f[a.length()][b.length()];
        }

    public:
        BKTree() { reset(); }

        void reset()
        {
            node_tail = nodes;
            root = 0;
        }

        void insert(const string &s) { insert(s, root); }
        void insert(const string &s, TNode *&node)
        {
            if (!node) {
                node = node_tail++;
                node->s = s;
                memset(node->next, 0, sizeof node->next);
                return ;
            }
            insert(s, node->next[diff(s, node->s)]);
        }

        int query(const string &s, int x) { return query(s, x, root); }
        int query(const string &s, int x, const TNode *node)
        {
            if (!node) return 0;

            int res = 0;
            int d = diff(s, node->s);
            if (d <= x) res++;
            for (int i = max(1, d - x); i <= min(MAXLEN - 1, d + x); i++) {
                res += query(s, x, node->next[i]);
            }
            return res;
        }
} bkt;

char strbuf[MAXLEN];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    for (int task = 1; task <= tasks; task++) {
        bkt.reset();
        printf("Case #%d:\n", task);

        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {

            scanf("%s", strbuf);
            bkt.insert(strbuf);
        }

        for (int i = 0; i < m; i++) {
            int x;
            scanf("%s%d", strbuf, &x);
            int r = bkt.query(strbuf, x);
            printf("%d\n", r);
        }
    }

    return 0;
}

