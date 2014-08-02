#include <cstdio>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    if (n < 9) puts("0");
    else if (n == 9) puts("8");
    else {
        printf("72");
        for (int i = 11; i <= n; i++) putchar('0');
        putchar(10);
    }

    return 0;
}
