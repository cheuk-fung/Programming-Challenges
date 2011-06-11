/*
 *  SRC: POJ 1005
 * PROB: I Think I Need a Houseboat
 * ALGO: Math
 * DATE: May 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>

const double pi = acos(-1);
const double eps = 1e-12;

void work(int k)
{
    double x, y;
    scanf("%lf%lf", &x, &y);

    int s = 0, ans = 0;
    double r = sqrt(x * x + y * y);
    while (1 + 1 == 2) {
        s += 100;
        ans++;
        if (sqrt(s / pi) - eps >= r) {
            printf("Property %d: This property will begin eroding in year %d.\n", k, ans);
            return ;
        }
    }
}

int main()
{
    int n, k = 0;
    scanf("%d", &n);
    while (n--) work(++k);

    puts("END OF OUTPUT.");
    
    return 0;
}

