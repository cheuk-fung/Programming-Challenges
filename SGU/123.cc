#include <cstdio>

int main(int argc, char *argv[])
{
    int k;
    scanf("%d", &k);

    int f[k + 1];
    int sum = 0;
    f[1] = 1; f[2] = 1;
    for (int i = 3; i <= k; i++) f[i] = f[i - 1] + f[i - 2];
    for (int i = 1; i <= k; i++) sum += f[i];

    printf("%d\n", sum);

    return 0;
}
