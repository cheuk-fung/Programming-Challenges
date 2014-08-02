/*
 *  SRC: NKOJ
 * TASK: Bug checker
 * ALGO: SPFA
 * DATE: 04/09/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>
using namespace std;

bool SPFA(int n, vector<int>* map, int start)
{
    bool used[1000];
    int query[10000];
    int lowest[1000], sum[1000];
    for (int i = 0; i < 1000; i++) {
        used[i] = false;
        lowest[i] = 10000000;
        sum[i] = 0;
    }
    int open = 0, closed = -1;
    used[start] = true;
    query[open] = start;
    lowest[start] = 0;
    while (closed < open) {
        long src = query[++closed];
        used[src] = false;
        int size = map[src].size();
        for (int i = 0; i < size; i++) {
            int dest = map[src][i];
            if (-1 + lowest[src] < lowest[dest]) {
                lowest[dest] = -1 + lowest[src];
                if (used[dest] == false) {
                    used[dest] = true;
                    query[++open] = dest;
                    sum[dest]++;
                    if (sum[dest] >= n) return false;
                }
            }
        }
    }
    return true;
}


void work()
{
    vector<int> map[1000];

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int I, Ni;
        scanf("%d%d", &I, &Ni);
        for (int j = 0; j < Ni; j++) {
            int t;
            scanf("%d", &t);
            map[I].push_back(t);
        }
    }
    //for (int i = 0; i < n; i++)
    if (SPFA(n, map, 0) == false) {
        printf("BUG\n");
        return ;
    }
    printf("AC\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        work();
    }

    return 0;
}

