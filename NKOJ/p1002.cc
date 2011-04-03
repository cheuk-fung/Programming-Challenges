/*
 *  SRC: NKOJ
 * TASK: [NKPC1]Lucy 的難題
 * ALGO: Math
 * DATE: 03/24/2011 
 *
 * Created by Leewings Ac
 */
 
#include <cstdio>
 
int f(int n)
{
    if (n >= 50025002) return n - 5;
    else return f(f(n + 2005));
}		/* -----  end of function f  ----- */
 
int main()
{
    int n;
    while(scanf("%d", &n) != -1) {
        if (n >= 50025002) printf("%d\n", n - 5);
        else printf("%d\n", f(n % 2000));
    }
 
    return 0;
}				/* ----------  end of function main  ---------- */
