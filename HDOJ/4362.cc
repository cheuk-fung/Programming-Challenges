/*
 *  SRC: HDOJ 4362
 * PROB: Dragon Ball
 * ALGO: DP
 * DATE: Aug 14, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

typedef pair<long long, int> pii;

const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

pii A[55][1010];
long long B[55][1010];
long long f[55][1010];

struct Node {
    long long v;
    long long x;
    int id;

    bool operator<(const Node &o) const { return v == o.v ? x > o.x : v > o.v; }
};

inline long long myabs(long long x) { return x >= 0 ? x : -x; }

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int m, n, tx;
        long long x;
        scanf("%d%d%d", &m, &n, &tx);
        x = tx;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &tx);
                A[i][j].first = tx;
                A[i][j].second = j;
            }
            sort(A[i], A[i] + n);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &tx);
                B[i][j] = tx;
            }
        }

        for (int i = 0; i < n; i++) f[0][i] = myabs(x - A[0][i].first) + B[0][A[0][i].second];
        for (int i = 1; i < m; i++) {
            priority_queue<Node> que;
            for (int j = 0; j < n; j++) {
                que.push((Node){f[i - 1][j] + myabs(A[i - 1][j].first - A[i][0].first), A[i - 1][j].first, j});
            }
            Node now = que.top();
            que.pop();
            for (int j = 0; j < n; j++) {
                while (!que.empty() && A[i - 1][que.top().id].first < A[i][j].first) {
                    if (f[i - 1][que.top().id] + myabs(A[i - 1][que.top().id].first - A[i][j].first) <= f[i - 1][now.id] + myabs(A[i - 1][now.id].first - A[i][j].first)) {
                        now = que.top();
                    }
                    que.pop();
                }
                while (!que.empty() && f[i - 1][que.top().id] + myabs(A[i - 1][que.top().id].first - A[i][j].first) <= f[i - 1][now.id] + myabs(A[i - 1][now.id].first - A[i][j].first)) {
                    now = que.top();
                    que.pop();
                }
                f[i][j] = f[i - 1][now.id] + myabs(A[i - 1][now.id].first - A[i][j].first) + B[i][A[i][j].second];
            }
        }

        long long ans = LLINF;
        for (int i = 0; i < n; i++) {
            ans = min(ans, f[m - 1][i]);
        }
        cout << ans << endl;
    }

    return 0;
}

