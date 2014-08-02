/*
 *  SRC: POJ 1731
 * PROB: Orders
 * ALGO: DFS
 * DATE: Jul 14, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using std::sort;
using std::next_permutation;

int main()
{
    char s[300];
    scanf("%s", s);

    int len = strlen(s);

    sort(s, s + len);
    do {
        puts(s);
    } while (next_permutation(s, s + len));

    return 0;
}
