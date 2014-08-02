#include <cstdio>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    int upper_left = 1, k = n, size = n;
    if (n % 2 == 0) {
        printf("%d", ++k);
        for (int i = upper_left; i < upper_left + n; i += 2) {
            printf(" %d", i);
        }
        for (int i = upper_left + n * 2; i < upper_left + n * n; i += n * 2) {
            printf(" %d", i);
        }
        putchar(10);

        printf("%d", k += 2);
        for (int i = upper_left + 1; i < upper_left + n; i += 2) {
            printf(" %d", i);
        }
        for (int i = upper_left + n; i < upper_left + n * n; i += n * 2) {
            printf(" %d", i);
        }
        putchar(10);

        upper_left += n + 1;
        k += 2;
        size--;
    }

    for ( ; size > 1; upper_left += n + 1, k += 2, size -= 2) {
        printf("%d", k);
        for (int i = upper_left; i < upper_left + size; i += 2) {
            printf(" %d", i);
        }
        for (int i = upper_left + n * 2; i < upper_left + n * (size - 1); i += n * 2) {
            printf(" %d %d", i, i + size - 1);
        }
        for (int i = upper_left + n * (size - 1); i < upper_left + n * (size - 1) + size; i += 2) {
            printf(" %d", i);
        }
        putchar(10);

        printf("%d", k += 2);
        for (int i = upper_left + 1; i < upper_left + size; i += 2) {
            printf(" %d", i);
        }
        for (int i = upper_left + n; i < upper_left + n * (size - 1); i += n * 2) {
            printf(" %d %d", i, i + size - 1);
        }
        for (int i = upper_left + n * (size - 1) + 1; i < upper_left + n * (size - 1) + size; i += 2) {
            printf(" %d", i);
        }
        putchar(10);
    }

    return 0;
}
