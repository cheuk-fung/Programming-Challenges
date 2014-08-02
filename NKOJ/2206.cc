/*
 *  SRC: NKOJ 2206
 * PROB: Cow Calisthenics
 * ALGO: Tree DP
 * DATE: Oct 27, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

enum {
    MAXN = 100000
};

int n, S;
vector<int> tree[MAXN];
int parent[MAXN], node_queue[MAXN];
int f[MAXN];

bool check(int x)
{
    int cnt = S;
    for (int i = n - 1; i >= 0; i--) {
        int u = node_queue[i];

        priority_queue<int> Q;
        Q.push(0);
        for (size_t j = 0; j < tree[u].size(); j++) {
            int v = tree[u][j];
            if (v == parent[u]) continue;
            if (f[v] + 1 + Q.top() > x) {
                if (--cnt < 0) return false;
                if (f[v] + 1 < Q.top()) {
                    Q.pop();
                    Q.push(f[v] + 1);
                }
            } else {
                Q.push(f[v] + 1);
            }
        }
        f[u] = Q.top();
    }

    return true;
}

int main()
{
    scanf("%d%d", &n, &S);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[--u].push_back(--v);
        tree[v].push_back(u);
    }

    int *head = node_queue, *tail = node_queue;
    *tail++ = 0;
    while (head != tail) {
        int u = *head++;
        for (size_t i = 0; i < tree[u].size(); i++) {
            int v = tree[u][i];
            if (v != parent[u]) {
                parent[v] = u;
                *tail++ = v;
            }
        }
    }

    int low = 0, high = MAXN;
    while (low < high) {
        int mid = (low + high - 1) >> 1;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }

    printf("%d\n", low);

    return 0;
}

