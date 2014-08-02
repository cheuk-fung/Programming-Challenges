#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Cell {
    char type;
    int cnt;
} row[200010];

struct Node {
    int id;
    int v;

    Node(int _id, int _v) : id(_id), v(_v) { }
    bool operator<(const Node &o) const { return v > o.v; }
};

priority_queue<Node> Q;
vector<int> dragon;

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf(" %c %d", &row[i].type, &row[i].cnt);
    }

    for (int i = 1; i < n - 1; i++) {
        if (row[i].type == 'd') {
            Q.push(Node(i, row[i].cnt));
        } else if (row[i].type == 'p') {
            while ((int)Q.size() >= row[i].cnt) Q.pop();
        }
    }

    if ((int)Q.size() < row[n - 1].cnt) {
        puts("-1");
    } else {
        int sum = 0;
        while (!Q.empty()) {
            sum += Q.top().v;
            dragon.push_back(Q.top().id + 1);
            Q.pop();
        }
        printf("%d\n", sum);
        sort(dragon.begin(), dragon.end());
        printf("%u\n", dragon.size());
        for (int i = 0; i < (int)dragon.size(); i++) {
            printf("%d%c", dragon[i], i + 1 == (int)dragon.size() ? '\n' : ' ');
        }
    }

    return 0;
}
