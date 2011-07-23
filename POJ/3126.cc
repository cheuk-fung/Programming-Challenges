/*
 *  SRC: POJ 3126
 * PROB: Prime Path
 * ALGO: BFS
 * DATE: Jul 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

struct Node {
    int p, t;

    Node(int _p, int _t)
        : p(_p), t(_t)
    { }
};

bool b[10000], visited[10000];
int p[10000];

int prime(int n)
{
    int sum = 0;
    b[0] = b[1] = false;
    for (int i = 2; i < n; i++) b[i] = true;
    for (int i = 2; i < n; i++) {
        if (b[i]) p[sum++] = i;
        for (int j = 0; j < sum && i * p[j] <= n; j++) {
            b[i * p[j]] = false;
            if (i % p[j] == 0) break;
        }
    }

    return sum;
}

int work()
{
    int start, end;
    scanf("%d%d", &start, &end);
    if (start == end) return 0;

    queue<Node> Q;
    Q.push(Node(start, 0));
    visited[start] = 1;
    while (!Q.empty()) {
        Node curr = Q.front();
        Q.pop();

        for (int i = 1; i < 10; i += 2) {
            int next = curr.p / 10 * 10 + i;
            if (next == end) return curr.t + 1;
            if (b[next] && !visited[next]) {
                Q.push(Node(next, curr.t + 1));
                visited[next] = 1;
            }
        }

        for (int i = 0; i < 10; i++) {
            int next = curr.p / 100 * 100 + i * 10 + curr.p % 10;
            if (next == end) return curr.t + 1;
            if (b[next] && !visited[next]) {
                Q.push(Node(next, curr.t + 1));
                visited[next] = 1;
            }
        }

        for (int i = 0; i < 10; i++) {
            int next = curr.p / 1000 * 1000 + i * 100 + curr.p % 100;
            if (next == end) return curr.t + 1;
            if (b[next] && !visited[next]) {
                Q.push(Node(next, curr.t + 1));
                visited[next] = 1;
            }
        }

        for (int i = 1; i < 10; i++) {
            int next = i * 1000 + curr.p % 1000;
            if (next == end) return curr.t + 1;
            if (b[next] && !visited[next]) {
                Q.push(Node(next, curr.t + 1));
                visited[next] = 1;
            }
        }
    }

    return -1;
}

int main()
{
    prime(10000);

    int t;
    scanf("%d", &t);
    while (t--) {
        int v = work();
        if (v == -1) puts("Impossible");
        else printf("%d\n", v);

        memset(visited, 0, sizeof(visited));
    }

    return 0;
}
