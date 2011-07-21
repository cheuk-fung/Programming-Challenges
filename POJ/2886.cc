/*
 *  SRC: POJ 2886
 * PROB: Who Gets the Most Candies?
 * ALGO: Segment Tree
 * DATE: Jul 21, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <cstring>

struct Node {
    int a, b;
    int cnt;
};

Node ST[2000000];

void STMake(int p, int a, int b)
{
    ST[p].a = a;
    ST[p].b = b;
    
    if (a + 1 < b) {
        STMake(p * 2, a, (a + b) / 2);
        STMake(p * 2 + 1, (a + b) / 2, b);
        ST[p].cnt = ST[p * 2].cnt + ST[p * 2 + 1].cnt;
    }
    else ST[p].cnt = 1;
}

void STDelete(int p, int c, int* pos)
{
    if (ST[p].a + 1 == ST[p].b) {
        ST[p].cnt--;
        *pos = ST[p].a;

        return ;
    }

    if (c <= ST[p * 2].cnt) STDelete(p * 2, c, pos);
    else STDelete(p * 2 + 1, c - ST[p * 2].cnt, pos);
    ST[p].cnt = ST[p * 2].cnt + ST[p * 2 + 1].cnt;
}

char name[500001][10];
int n, m, val[500001];

int prm[] = {
    1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840,
    1260, 1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200,
    27720, 45360, 50400, 55440, 83160, 110880, 166320, 221760,
    277200, 332640, 498960, 500001 // add 500001 just for stopping the loop using prm below
};
int div[] = {
    1, 2, 3, 4, 6, 8, 9, 10, 12, 16, 18, 20, 24, 30, 32, 36, 40,
    48, 60, 64, 72, 80, 84, 90, 96, 100, 108, 120, 128, 144, 160,
    168, 180, 192, 200
};

int main()
{
    while (scanf("%d%d", &n, &m) != EOF) {
        STMake(1, 1, n + 1);

        for (int i = 1; i <= n; i++)
            scanf("%s%d", name[i], val + i);

        int finish = 0;
        while (n >= prm[finish]) finish++;
        finish--;

        int pos = 0;
        for (int i = 0; i < prm[finish]; i++) {
            STDelete(1, m, &pos);
            if (ST[1].cnt == 0) break;
            if (val[pos] > 0) {
                m = (m - 1 + val[pos]) % ST[1].cnt;
                if (m == 0) m = ST[1].cnt;
            }
            else {
                m = (m + val[pos] % ST[1].cnt + ST[1].cnt) % ST[1].cnt;
                if (m == 0) m = ST[1].cnt;
            }
        }

        printf("%s %d\n", name[pos], div[finish]);
    }

    return 0;
}
