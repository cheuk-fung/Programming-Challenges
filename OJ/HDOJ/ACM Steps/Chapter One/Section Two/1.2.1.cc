/*
 *  SRC: HDOJ ACM Steps
 * PROB: Rightmost Digit
 * ALGO: NULL
 * DATE: Oct 29, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int ans[10][4] = {
    {0},
    {1},
    {6, 2, 4, 8},
    {1, 3, 9, 7},
    {6, 4},
    {5},
    {6},
    {1, 7, 9, 3},
    {6, 8, 4, 2},
    {1, 9}
};
int cnt[10] = {1, 1, 4, 4, 2, 1, 1, 4, 4, 2};

inline void work()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", ans[n % 10][n % cnt[n % 10]]);
}

int main()
{
    int jobs;
    scanf("%d", &jobs);
    while (jobs--) work();

    return 0;
}
