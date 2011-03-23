/*
 *  SRC: NKOJ
 * TASK: 多項式輸出
 * ALGO: NULL
 * DATE: 03/22/2011 
 *
 * Created by Leewings Ac
 */

#include	<cstdio>
#include	<cstdlib>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        int a;
        scanf("%d", &a);
        if (i == 0) {
            if (a < 0) printf("-");
            if (abs(a) != 1) printf("%d", abs(a));
            printf("x^%d", n);
        }
        else if (a) {
            a > 0 ? printf("+") : printf("-");
            if (n - i) {
                if (abs(a) != 1) printf("%d", abs(a));
                printf("x");
                if (n - i > 1) printf("^%d", n - i);
            }
            else printf("%d", abs(a));
        }
    }
    printf("\n");

    return 0;
}				/* ----------  end of function main  ---------- */
