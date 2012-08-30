/*
 *  SRC: HDOJ 4054
 * PROB: Hexadecimal View
 * ALGO: NULL
 * DATE: Aug 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cctype>

char line[5000];

inline char change(char c)
{
    if (islower(c)) return toupper(c);
    if (isupper(c)) return tolower(c);
    return c;
}

int main()
{
    while (gets(line)) {
        int len = strlen(line);
        for (int i = 0; i < len / 16; i++) {
            printf("%04x: ", i * 16);
            for (int j = i * 16; j < i * 16 + 16; j += 2) {
                printf("%02x%02x ", line[j], line[j + 1]);
                line[j] = change(line[j]);
                line[j + 1] = change(line[j + 1]);
            }
            for (int j = i * 16; j < i * 16 + 16; j++) putchar(line[j]);
            putchar(10);
        }
        if (len % 16) {
            printf("%04x: ", len / 16 * 16);
            int offset = 0;
            for (int j = len / 16 * 16; j < len; j += 2) {
                printf("%02x", line[j]);
                line[j] = change(line[j]);
                if (j + 1 < len) {
                    printf("%02x ", line[j + 1]);
                    line[j + 1] = change(line[j + 1]);
                } else {
                    printf("   ");
                    offset = 1;
                }
            }
            for (int j = len % 16 + offset; j < 16; j += 2) printf("     ");
            for (int j = len / 16 * 16; j < len; j++) putchar(line[j]);
            putchar(10);
        }
    }

    return 0;
}

