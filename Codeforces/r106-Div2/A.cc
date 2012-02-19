#include <cstdio>
#include <algorithm>

using std::sort;

int k, a[12];

int solve()
{
    if (!k) return 0;
    sort(a, a + 12);
    for (int i = 11, tot = 0; i >= 0; i--) {
        tot += a[i];
        if (tot >= k) return 12 - i;
    }
    return -1;
}

int main()
{
    scanf("%d", &k);
    for (int i = 0; i < 12; i++) scanf("%d", a + i);
    printf("%d\n", solve());

    return 0;
}

