/*
 *  SRC: POJ 3278
 * PROB: Catch That Cow
 * ALGO: BFS
 * DATE: Jul 23, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <queue>

using std::queue;

struct Node {
    int pos, time;

    Node(int _pos, int _time)
        : pos(_pos), time(_time)
    { }
};

int n, k, ans;
int visited[200012];
queue<Node> Q;

int main()
{
    scanf("%d%d", &n, &k);

    if (n == k) {
        puts("0");
        return 0;
    }

    Q.push(Node(n, 0));
    while (!Q.empty()) {
        Node p = Q.front();
        Q.pop();

        if (!visited[p.pos + 1]) {
            if (p.pos + 1 == k) {
                ans = p.time + 1;
                break;
            }
            Q.push(Node(p.pos + 1, p.time + 1));
            visited[p.pos + 1] = 1;
        }
        if (p.pos && !visited[p.pos - 1]) {
            if (p.pos - 1 == k) {
                ans = p.time + 1;
                break;
            }
            Q.push(Node(p.pos - 1, p.time + 1));
            visited[p.pos - 1] = 1;
        }
        if (p.pos * 2 <= k * 2 && !visited[p.pos * 2]) {
            if (p.pos * 2 == k) {
                ans = p.time + 1;
                break;
            }
            Q.push(Node(p.pos * 2, p.time + 1));
            visited[p.pos * 2] = 1;
        }
    }

    printf("%d\n", ans);

    return 0;
}
