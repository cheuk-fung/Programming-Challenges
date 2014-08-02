/*
 *  SRC: POJ 1006
 * PROB: Biorhythms
 * ALGO: Number Theory
 * DATE: May 10, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int main()
{
    int n = 0;
    while (1 + 1 == 2) {
        int p, e, i ,d;
        scanf("%d%d%d%d", &p, &e, &i, &d);
        if (p == e && e == i && i == d && d == -1) break; 

        int a = 5544;
        int b = 14421;
        int c = 1288;
        int ans = (a * p + b * e + c * i) % 21252 - d;
        if (ans <= 0) ans += 21252;
        printf("Case %d: the next triple peak occurs in %d days.\n", ++n, ans);
        
        /*
        int x = 0, y = 0, z = 0;
        while (1 + 1 == 2) {
            int a = p + 23 * x, b = e + 28 * y, c = i + 33 * z;
            if (a < b) x++;
            else if (a > b) y++;
            if (b < c) y++;
            else if (b > c) z++;
            if (a == b && b == c) {
                int ans = a - d;
                while (ans <= 0) ans += 23 * 28 * 33;
                while (ans > 23 * 28 * 33) ans -= 23 * 28 * 33;
                printf("Case %d: the next triple peak occurs in %d days.\n", ++n, ans);
                break;
            }
        }
        */
    }

    return 0;
}

