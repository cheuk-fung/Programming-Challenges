/*
 *  SRC: NKOJ p1324
 * PROB: Sorting It All Out
 * ALGO: Topological Sort
 * DATE: Jul 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

int n, m;
int degree[255], map[255][255];
bool exist[255];
queue<char> Q;

int check()
{
    // 0: Sorted sequence determined after xxx relations: yyy...y.
    // 1: Sorted sequence cannot be determined.
    // 2: Inconsistency found after xxx relations. 

    while (!Q.empty()) Q.pop();

    int deg[255];
    for (int i = 'A'; i < 'A' + n; i++)
        deg[i] = degree[i];

    bool conflict = false;
    while (1 + 1 == 2) {
        bool flag = false;
        for (int i = 'A'; i < 'A' + n; i++) {
            if (deg[i] == 0) {
                if (flag) conflict = true;
                flag = true;
            }
        }
        if (!flag) break;

        for (int i = 'A'; i < 'A' + n; i++) {
            if (deg[i] == 0) {
                Q.push(i);

                for (int j = 'A'; j < 'A' + n; j++)
                    if (map[i][j]) deg[j] -= map[i][j];

                deg[i]--;

                break;
            }
        }
    }

    for (int i = 'A'; i < 'A' + n; i++)
        if (deg[i] >= 0) return 2;

    if (conflict) return 1;

    return 0;
}

bool solve()
{
    scanf("%d%d", &n, &m);
    if (n == 0 && m == 0) return false;

    memset(map, 0, sizeof(map));
    memset(degree, 0, sizeof(degree));
    memset(exist, false, sizeof(exist));

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        char s[4];
        scanf("%s", s);

        map[s[0]][s[2]]++;
        degree[s[2]]++;
        if (cnt < n) {
            if (!exist[s[0]]) {
                cnt++;
                exist[s[0]] = true;
            }
            if (!exist[s[2]]) {
                cnt++;
                exist[s[2]] = true;
            }
        }

        int p = check();

        if (p == 0 && cnt == n) {
            printf("Sorted sequence determined after %d relations: ", i + 1);
            while (!Q.empty()) {
                putchar(Q.front());
                Q.pop();
            }
            printf(".\n");

            for (int j = i + 1; j < m; j++) scanf("%s", s);

            return true;
        }

        if (p == 2) {
            printf("Inconsistency found after %d relations.\n", i + 1);

            for (int j = i + 1; j < m; j++) scanf("%s", s);

            return true;
        }
    }

    printf("Sorted sequence cannot be determined.\n");

    return true;
}

int main()
{
    while (solve()) ;

    return 0;
}

