/*
 *  SRC: ZOJ 3542
 * PROB: Hexadecimal View
 * ALGO: NULL
 * DATE: Oct 02, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cctype>

char str[5000];

int main()
{
    while (gets(str)) {
        int line = 0;

        char *ptr = str;
        ptr = str;
        while (*ptr) {
            printf("%04x: ", line);
            for (int i = 0; i < 8; i++) {
                if (*(ptr + i * 2)) {
                    printf("%02x", *(ptr + i * 2));
                    if (*(ptr + i * 2 + 1)) printf("%02x ", *(ptr + i * 2 + 1));
                    else {
                        printf("   ");
                        for (i++; i < 8; i++) printf("     ");
                    }
                }
                else for ( ; i < 8; i++) printf("     ");
            }
            for (int i = 0; i < 16; i++) {
                if (islower(*ptr)) putchar(toupper(*ptr++));
                else if (isupper(*ptr)) putchar(tolower(*ptr++));
                else putchar(*ptr++);
                if (!*ptr) break;
            }
            putchar(10);
            line += 16;
        }
    }

    return 0;
}
