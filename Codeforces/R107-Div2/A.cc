#include <cstdio>
#include <algorithm>

using std::min;

int main()
{
    int n, k, l, c, d, p, nl, np;
    scanf("%d%d%d%d%d%d%d%d", &n, &k, &l, &c, &d, &p, &nl, &np);
    int ans = k * l / (nl * n);
    ans = min(ans, c * d / n);
    ans = min(ans, p / (np * n));
    printf("%d\n", ans);

    return 0;
}

