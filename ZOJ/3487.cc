/*
 *  SRC: ZOJ 3487
 * PROB: Ordinal Numbers
 * ALGO: NULL
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        if (n % 100 / 10 == 1) printf("%dth\n", n);
        else if (n % 10 == 1) printf("%dst\n", n);
        else if (n % 10 == 2) printf("%dnd\n", n);
        else if (n % 10 == 3) printf("%drd\n", n);
        else printf("%dth\n", n);
    }

    return 0;
}

