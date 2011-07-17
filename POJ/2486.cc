/*
 *  SRC: POJ 2486
 * PROB: Apple Tree
 * ALGO: Tree DP
 * DATE: Jul 17, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>

using std::vector;

struct Node {
    int id;
    Node* l;
    Node* r;

    Node(int _id) : id(_id), l(0), r(0) { }
    ~Node() {
        if (l) delete l;
        if (r) delete r;
    }
};

int n, m;
int app[110];
int f[2][110][210];

vector<int> adj[110];
typedef vector<int>::const_iterator cit;
int used[110];

inline int max(int a, int b)
{
    return a > b ? a : b;
}

void makeTree(const cit it, const cit end, Node* p)
{
    if (used[*it]) {
        if (it + 1 != end)
            makeTree(it + 1, end, p);
        return ;
    }

    used[*it] = 1;

    // turn Node p's next brother into its right child
    for (int i = 0; it + i != end; i++)
        if (!used[*(it + i)]) {
            p->r = new Node(*(it + i));
            makeTree(it + i, end, p->r);
            break;
        }

    // turn Node p's first child into its left child
    for (int i = 0; i < adj[*it].size(); i++)
        if (!used[adj[*it][i]]) {
            p->l = new Node(adj[*it][i]);
            makeTree(adj[*it].begin() + i, adj[*it].end(), p->l);
            break;
        }
}

int dp(const Node* p, int c, int m)
{
    if (p == 0) return 0;

    int id = p->id;

    if (f[c][id][m] > -1) return f[c][id][m];

    if (p->l == 0 && p->r == 0)
        return f[c][id][m] = app[id];

    if (m == 0)
        return f[c][id][m] = max(app[id], dp(p->r, c, m));

    if (c == 0) {
        int t = dp(p->r, 0, m);
        if (m >= 2) {
            t = max(t, dp(p->l, 0, m - 2) + app[id]);
            t = max(t, dp(p->r, 0, m - 2) + app[id]);
        }

        for (int i = 0; i <= m - 4; i++)
            t = max(t, dp(p->l, 0, i) + dp(p->r, 0, m - 4 - i) + app[id]);

        return f[c][id][m] = t;
    }
    else {
        int t = dp(p->r, 1, m);
        t = max(t, dp(p->l, 1, m - 1) + app[id]);

        if (m >= 2)
            t = max(t, dp(p->r, 1, m - 2) + app[id]);

        for (int i = 0; i <= m - 4; i++)
            t = max(t, dp(p->l, 0, i) + dp(p->r, 1, m - 4 - i) + app[id]);

        for (int i = 0; i <= m - 3; i++)
            t = max(t, dp(p->l, 1, i) + dp(p->r, 0, m - 3 - i) + app[id]);

        return f[c][id][m] = t;
    }

    return f[c][id][m];
}

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", app + i);

        if (n == 1) {
            printf("%d\n", app[0]);

            continue;
        }

        for (int i = 0; i < n; i++)
            adj[i].clear();

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            adj[a - 1].push_back(b - 1);
            adj[b - 1].push_back(a - 1);
        }

        memset(f, -1, sizeof(f));
        memset(used, 0, sizeof(used));

        used[0] = 1;
        Node* tree = new Node(0);
        tree->l = new Node(adj[0][0]);
        makeTree(adj[0].begin(), adj[0].end(), tree->l);

        printf("%d\n", dp(tree, 1, m));
    }

    return 0;
}
