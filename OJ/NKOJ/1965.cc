/*
 *  SRC: NKOJ 1965
 * PROB: The Seven Percent Solution
 * ALGO: String
 * DATE: Aug 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    char c;
    while ((c = getchar()) != '#') {
        switch(c) {
            case ' ': printf("%%20"); break;
            case '!': printf("%%21"); break;
            case '$': printf("%%24"); break;
            case '%': printf("%%25"); break;
            case '(': printf("%%28"); break;
            case ')': printf("%%29"); break;
            case '*': printf("%%2a"); break;
            default: putchar(c);
        }
    }

    return 0;
}
