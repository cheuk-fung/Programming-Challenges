/*
 *  SRC: POJ 3349
 * PROB: Snowflake Snow Snowflakes
 * ALGO: hash
 * DATE: Jul 19, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

const int MOD = 999997;

struct Link {
    int flag, a[6];
    Link* next;
} table[MOD];

int BKDRHash(int *a)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    for (int i = 0; i < 6; i++)
        hash = hash * seed + a[i];

    return (hash & 0x7FFFFFFF) % MOD;
}

int hash(int* a)
{
    int cw = 0;
    for (int i = 1; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            if (*(a + (i + j) % 6) > *(a + (cw + j) % 6)) break;
            if (*(a + (i + j) % 6) < *(a + (cw + j) % 6)) {
                cw = i;
                break;
            }
        }

    int ccw = 0;
    for (int i = 1; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            if (*(a + (i - j + 6) % 6) > *(a + (ccw - j + 6) % 6)) break;
            if (*(a + (i - j + 6) % 6) < *(a + (ccw - j + 6) % 6)) {
                ccw = i;
                break;
            }
        }

    int max = 1;
    for (int i = 0; i < 6; i++) {
        if (*(a + (cw + i) % 6) < *(a + (ccw - i + 6) % 6)) break;
        if (*(a + (cw + i) % 6) > *(a + (ccw - i + 6) % 6)) {
            max = 0;
            break;
        }
    }

    int b[6];
    if (max)
        for (int i = 0; i < 6; i++)
            b[i] = *(a + (cw + i) % 6);
    else
        for (int i = 0; i < 6; i++)
            b[i] = *(a + (ccw - i + 6) % 6);

    memcpy(a, b, sizeof(int) * 6);

    return BKDRHash(a);
}

int insert(int val, int* a)
{
    Link* l = &table[val];
    if (!l->flag) {
        memcpy(l->a, a, sizeof(int) * 6);
        l->flag = 1;

        return 0;
    }

OUTER_LOOP:
    while (l) {
        for (int i = 0; i < 6; i++)
            if (a[i] != l->a[i]) {
                if (l->next == 0) {
                    l->next = new Link;
                    l = l->next;
                    l->next = 0;
                    memcpy(l->a, a, sizeof(int) * 6);

                    return 0;
                }
                else l = l->next;

                goto OUTER_LOOP;
            }

        return 1;
    }
}

int main()
{
    int n, snow[6];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++)
            scanf("%d", snow + j);

        int val = hash(snow);
        if (insert(val, snow)) {
            puts("Twin snowflakes found.");

            return 0;
        }
    }

    puts("No two snowflakes are alike.");

    return 0;
}
