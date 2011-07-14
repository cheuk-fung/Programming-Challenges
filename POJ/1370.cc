/*
 *  SRC: POJ 1370
 * PROB: Gossiping
 * ALGO: Number Theory
 * DATE: Jul 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int n, d, s;
int l[64], fro[64], initTime[64][64];
bool stop[64][64], conn[64][64], visited[64];

bool check()
{
    queue<int> que;

    que.push(0);
    visited[0] = true;
    int cnt = 1;

    while (!que.empty()) {
        int p = que.front();
        que.pop();
        visited[p] = true;
        for (int i = 0; i < d; i++)
            if (conn[p][i] && !visited[i]) {
                que.push(i);
                visited[i] = true;
                cnt++;
            }
    }

    return cnt == d;
}

bool solve()
{
    scanf("%d%d%d", &n, &d, &s);
    if (!(n || d || s)) return false;

    memset(stop, false, sizeof(stop));
    memset(conn, false, sizeof(conn));
    memset(visited, false, sizeof(visited));

    for (int i = 0; i < n; i++) {
        vector<int> line;
        char c = 0;
        while (c != '\n') {
            int t;
            scanf("%d", &t);
            line.push_back(t - 1);
            c = getchar();
        }
        l[i] = line.size();

        c = 0;
        while (c != '\n') {
            int s, d;
            scanf("%d%d", &s, &d);
            fro[d - 1] = i;
            
            int k = 0;
            for (int j = 0; j < line.size(); j++)
                if (line[j] == s - 1) {
                    k = j;
                    break;
                }
            for (int j = 0; j < line.size(); j++) {
                int st = line[(k + j) % line.size()];
                initTime[st][d - 1] = j;
                stop[st][d - 1] = true;
            }
            c = getchar();
        }
    }

    for (int i = 0; i < s; i++) // the ith stop
        for (int j = 0; j < d; j++) // the jth driver
            if (stop[i][j]) {
                for (int k = 0; k < d; k++) // the kth driver
                    if (j != k && stop[i][k] && !conn[j][k]) {
                        int s1 = l[fro[j]];
                        int s2 = l[fro[k]];
                        int a = initTime[i][j];
                        int b = initTime[i][k];

                        if ((a - b) % gcd(s1, s2) == 0)
                            conn[j][k] = conn[k][j] = true;
                    }
            }

    if (check()) puts("Yes");
    else puts("No");

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}
