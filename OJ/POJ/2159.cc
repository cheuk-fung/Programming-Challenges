/*
 *  SRC: POJ 2159
 * PROB: Ancient Cipher
 * ALGO: NULL
 * DATE: May 9, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int sumA[300], sumB[300];
int totA[300], totB[300];

int main()
{
    char a[200], b[200];
    scanf("%s%s", a, b);
    int len = strlen(a);
    for (int i = 0; i < len; i++) {
        sumA[a[i]]++;
        sumB[b[i]]++;
    }
    for (int i = 0; i < 300; i++) {
        totA[sumA[i]]++;
        totB[sumB[i]]++;
    }
    for (int i = 0; i < 300; i++) {
        if (totA[i] != totB[i]) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");

    return 0;
}

