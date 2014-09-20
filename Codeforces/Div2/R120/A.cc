#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        if (n == 0) {
            if (m) puts("Impossible");
            else puts("0 0");
        } else {
            printf("%d %d\n", max(n, m), max(n, n + m - 1));
        }
    }

    return 0;
}

