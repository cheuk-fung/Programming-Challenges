/*
 *  SRC: POJ
 * TASK: A DP Problem
 * ALGO: string
 * DATE: 05/23/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

void work()
{
    char ss[300];
    scanf("%s", ss);
    char* s = ss;

    int fac = 0, num = 0;
    int sign = 1; // 1 for '+', -1 for '-'
    int isLeft = 1; // 1 for the left part of the equation, -1 for the right
    int cnt = 0;
    while (*s) {
        switch (*s) {
            case '+':
                num += cnt * sign * isLeft;
                cnt = 0;
                sign = 1;
                s++;
                break;
            case '-':
                num += cnt * sign * isLeft;
                cnt = 0;
                sign = -1;
                s++;
                break;
            case '=':
                num += cnt * sign * isLeft;
                cnt = 0;
                sign = 1;
                isLeft = -1;
                s++;
                break;
            case 'x':
                if (cnt == 0) cnt = 1;
                fac += cnt * sign * isLeft;
                cnt = 0;
                s++;
                break;
            default:
                cnt = cnt * 10 + (*s - '0');
                s++;
        }
    }
    num += cnt * sign * isLeft;

    if (fac == 0) {
        if (num == 0) puts("IDENTITY");
        else puts("IMPOSSIBLE");
        return ;
    }

    printf("%d\n", int(floor(-1.0 * num / fac)));
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) work();

    return 0;
}

