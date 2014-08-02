#include <cstdio>

inline int f(int n)
{
    n %= 9;
    return n ? n : 9;
}

int main(int argc, char *argv[])
{
    int k;
    scanf("%d", &k);
    while (k--) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        int last = 1;
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            last = f(last * f(a));
            ans = f(last + ans);
        }
        printf("%d\n", ans);
    }

    return 0;
}
