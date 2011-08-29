/*
 *  SRC: POJ 3566
 * PROB: Building for UN
 * ALGO: NULL
 * DATE: Aug 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

char letter[100];

int main()
{
    int cnt = 0;
    for (int i = 'a'; i <= 'z'; i++) letter[cnt++] = i;
    for (int i = 'A'; i <= 'Z'; i++) letter[cnt++] = i;

    int n;
    scanf("%d", &n);

    printf("%d %d %d\n", n, n, 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) putchar(letter[j]);
        putchar(10);
        for (int j = 0; j < n; j++) putchar(letter[i]);
        putchar(10);
        putchar(10);
    }

    return 0;
}
