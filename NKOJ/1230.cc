/*
 *  SRC: NKOJ 1230
 * PROB: Counterfeit Dollar
 * ALGO: Brute Force
 * DATE: Sep 20, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

char left[3][10], right[3][10], buf[10];
int l_len[3], r_len[3];

enum Balance { even, up, down };
enum Weight { heavy, light };
enum Side { l, r, n };

Balance b[3];
Side s[3];

Side find(int p, char c)
{
    for (int i = 0; i < l_len[p]; i++)
        if (left[p][i] == c) return l;
    for (int i = 0; i < r_len[p]; i++)
        if (right[p][i] == c) return r;
    return n;
}

bool check(int p, char c, Weight w)
{
    if (p == 3) return true;

    switch(s[p]) {
        case n:
            if (b[p] != even) return false;
            break;
        case l:
            if (b[p] != (w == heavy ? up : down)) return false;
            break;
        case r:
            if (b[p] != (w == heavy ? down : up)) return false;
    }

    return check(p + 1, c, w);
}

void work()
{
    for (int i = 0; i < 3; i++) {
        scanf("%s%s%s", left[i], right[i], buf);
        l_len[i] = strlen(left[i]);
        r_len[i] = strlen(right[i]);

        if (!strcmp(buf, "even")) b[i] = even;
        else if (!strcmp(buf, "up")) b[i] = up;
        else if (!strcmp(buf, "down")) b[i] = down;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        s[0] = find(0, c);
        s[1] = find(1, c);
        s[2] = find(2, c);
        if (check(0, c, heavy)) {
            printf("%c is the counterfeit coin and it is %s.\n", c, "heavy");
            return ;
        }
        if (check(0, c, light)) {
            printf("%c is the counterfeit coin and it is %s.\n", c, "light");
            return ;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    while (n--) work();

    return 0;
}
