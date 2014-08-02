#include <cstdio>

int main(int argc, char *argv[])
{
    unsigned int n;
    scanf("%u", &n);
    printf("%u\n", n * (n + 1) / 2 + 1);

    return 0;
}
