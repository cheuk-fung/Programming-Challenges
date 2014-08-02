/*
 *  SRC: NKOJ
 * TASK: a^b
 * ALGO: Number Theory
 * DATE: 03/20/2011 
 *
 * Created by Leewings Ac
 */

#include	<cstdio>

using namespace std;

int solve(int a, int b)
{
    int res = 1;
    while (b) {
        if (b & 1) {
            res *= a;
            res %= 9;
        }
        b >>= 1;
        a *= a;
        a %= 9;
    }
    if (res == 0) {
        res = 9;
    }
    return res;
}		/* -----  end of function solve  ----- */

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    while (a || b) {
        printf("%d\n", solve(a, b));
        scanf("%d%d", &a, &b);
    }
    
    return 0;
}				/* ----------  end of function main  ---------- */

