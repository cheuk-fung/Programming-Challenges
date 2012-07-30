#include <cstdio>

int main(int argc, char *args[])
{
    int n;
    scanf("%d", &n);
    printf("%d\n", n / 3 * 2 + (n % 3 == 2));

    return 0;
}
