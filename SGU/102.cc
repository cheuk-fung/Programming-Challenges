#include <cstdio>
#include <algorithm>

using std::__gcd;

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (__gcd(i, n) == 1) {
            cnt++;
        }
    }

    printf("%d\n", cnt);

    return 0;
}
