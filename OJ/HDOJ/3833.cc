/*
 *  SRC: HDOJ 3833
 * PROB: YY's new problem
 * ALGO: NULL
 * DATE: Apr 11, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cctype>

int permutation[10010];

int next_int()
{
    char c;
    while (isspace(c = getchar())) ;
    int res = c - '0';

    while (isdigit(c = getchar())) {
        res = res * 10 + c - '0';
    }

    return res;
}

bool check(int n)
{
    for (int i = 2; i <= n; i++) {
        for (int j = i - 1; j > 0; j--) {
            int k = i * 2 - j;
            if (k > n) continue;
            if (permutation[j] < permutation[i] && permutation[i] < permutation[k])
                return true;
            if (permutation[j] > permutation[i] && permutation[i] > permutation[k])
                return true;
        }
    }

    return false;
}

int main()
{
    int tasks = next_int();
    while (tasks--) {
        int n = next_int();
        for (int i = 0; i < n; i++) {
            permutation[next_int()] = i;
        }

        puts(check(n) ? "Y" : "N");
    }

    return 0;
}

