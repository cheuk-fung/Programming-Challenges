/*
 *  SRC: POJ 3768
 * PROB: Repeater
 * ALGO: D&C
 * DATE: Jun 7, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <cmath>

int n, q, cnt;

void repeat(int qq, char** line, char** tmpl)
{
    if (qq == q) {
        int size = pow(n, q);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++)
                putchar(line[i][j]);
            putchar(10);
        }

        return ;
    }

    for (int i = 0; i < n; i++) {
        char** nextLine;
        nextLine = new char*[n];
        int nextSize = pow(n, qq + 1);
        for (int j = 0; j < n; j++) {
            nextLine[j] = new char[nextSize];
            memset(nextLine[j], ' ', nextSize);
        }

        int size = pow(n, qq);
        for (int j = 0; j < size; j++)
            if (line[i][j] != ' ')
                for (int a = 0; a < n; a++)
                    for (int b = 0; b < n; b++)
                        nextLine[a][j * n + b] = tmpl[a][b];

        repeat(qq + 1, nextLine, tmpl);
    }
}

bool work()
{
    scanf("%d", &n);
    if (n == 0) return false;

    char** tmpl;
    tmpl = new char*[n];

    for (int i = 0; i < n; i++) {
        tmpl[i] = new char[n];
        for (int j = 0; j < n; j++)
            while ((tmpl[i][j] = getchar()) == '\n') ;
    }

    scanf("%d", &q);

    repeat(1, tmpl, tmpl);

    return true;
}

int main()
{
    while (work()) ;
    return 0;
}

