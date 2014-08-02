#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1001;
bool isfriend[MAXN][MAXN];
int cycle[MAXN];

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        while (true) {
            int j;
            scanf("%d", &j);
            isfriend[i][j] = true;
            char c = getchar();
            if (c == '\n' || c == '\r' || c == EOF) break;
        }
    }

    for (int i = 0; i < n; i++) cycle[i] = i + 1;
    for (int times = 0; times < n; times++) {
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if (!isfriend[cycle[i]][cycle[j]]) {
                for (int k = 0; k < n; k++) {
                    int l = (k + 1) % n;
                    if (i == k || i == l || j == k || j == l) continue;
                    if (isfriend[cycle[i]][cycle[k]] && isfriend[cycle[j]][cycle[l]]) {
                        if (j < k) {
                            reverse(cycle + j, cycle + k + 1);
                        } else {
                            reverse(cycle + l, cycle + i + 1);
                        }
                        break;
                    }
                }
                break;
            }
        }
    }

    int first = 0;
    while (cycle[first] != 1) first++;
    for (int i = 0; i < n; i++) {
        printf("%d ", cycle[(first + i) % n]);
    }
    puts("1");

    return 0;
}
