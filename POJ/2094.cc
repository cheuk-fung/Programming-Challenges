/*
 *  SRC: POJ
 * TASK: Angry Teacher
 * ALGO: Math & BigInteger
 * DATE: 05/25/2011 
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

int n, k, m;
long long l[310];
long long a[20][310];
long long table[20][1010][310];

void str2num(long long* a, const char* s)
{
    int p = 0, len = strlen(s);
    while (len) {
        if (len >= 4) {
            len -= 4;
            const char* t = s + len;
            a[p] = 0;
            for (int i = 0; i < 4; i++)
                a[p] = a[p] * 10 + (t[i] - '0');
        }
        else {
            a[p] = 0;
            for (int i = 0; i < len; i++)
                a[p] = a[p] * 10 + (s[i] - '0');
            len = 0;
        }
        p++;
    }
}

inline void upgrade(long long* num, int p)
{
    while (num[p] >= 10000) {
        num[p + 1] += num[p] / 10000;
        num[p++] %= 10000;
    }
    num[300] %= 10000;
}

inline void downgrade(long long* num, int p)
{
    while (p <= 300 && num[p] < 0) {
        while (num[p] < 0) {
            num[p + 1]--;
            num[p] += 10000;
        }
        p++;
    }
    num[300] %= 10000;
}

void plus(long long* a, const long long* b)
{
    for (int i = 0; i <= 300; i++) {
        a[i] += b[i];
        upgrade(a, i);
    }
}

void minus(long long* a, const long long* b)
{
    for (int i = 0; i <= 300; i++) {
        a[i] -= b[i];
        downgrade(a, i);
    }
}

void multiply(long long* a, const long long* b)
{
    long long res[310];
    memset(res, 0, sizeof(res));
    for (int i = 0; i <= 300; i++)
        for (int j = 0; j <= 300; j++)
            if (i + j <= 300) res[i + j] += a[i] * b[j];
    for (int i = 0; i <= 300; i++) upgrade(res, i);
    memcpy(a, res, sizeof(res));
}

void calc(long long* num)
{
    long long at[310], mt[310];
    memset(mt, 0, sizeof(mt));
    mt[0] = 1;

    memcpy(num, a[n], sizeof(a[n]));

    for (int i = n - 1; i >= 0; i--) {
        multiply(mt, l);
        memcpy(at, a[i], sizeof(a[i]));
        multiply(at, mt);
        plus(num, at);
    }

    l[0]++;
    upgrade(l, 0);
}

void print(long long* num)
{
    int p = 200;
    while (p > 0 && num[p] == 0) p--;
    printf("%lld", num[p--]);
    while (p >= 0) {
        if (num[p] < 1000) putchar('0');
        if (num[p] < 100) putchar('0');
        if (num[p]< 10) putchar('0');
        printf("%lld", num[p--]);
    }
    putchar(10);
}

void getAns(long long* num)
{
    int ans = 0, p = 0, len = m;
    while (len) {
        int t = num[p];
        if (len >= 4) {
            len -= 4;
            for (int i = 0; i < 4; i++) {
                ans += (t % 10) * (t % 10);
                t /= 10;
            }
        }
        else {
            for (int i = 0; i < len; i++) {
                ans += (t % 10) * (t % 10);
                t /= 10;
            }
            len = 0;
        }
        p++;
    }

    printf("%d\n", ans);
}

int main()
{
    /*
    m = 100;
    int aaa[310], bbb[310];
    memset(aaa, 0, sizeof(aaa));
    memset(bbb, 0, sizeof(bbb));
    str2num(aaa, "123000000004560000007890");
    getAns(aaa);
    str2num(bbb, "9876500000000430000000021000");
    getAns(bbb);
    print(aaa);
    print(bbb);
    plus(aaa, bbb);
    print(aaa);
    minus(aaa, bbb);
    print(aaa);
    multiply(aaa, bbb);
    print(aaa);
    return 0;
    */

    scanf("%d", &n);
    char s[2000];
    scanf("%s", s);
    str2num(l, s);

    scanf("%d%d", &k, &m);
    for (int i = 0; i <= n; i++) {
        scanf("%s", s);
        str2num(a[i], s);
    }

    for (int i = 0; i < n + 1; i++) calc(table[0][i]);

    for (int i = 1; i < n + 1; i++)
        for (int j = 0; j < n + 1 - i;  j++) {
            memcpy(table[i][j], table[i - 1][j + 1], sizeof(table[i][j]));
            minus(table[i][j], table[i - 1][j]);
        }

   if (k <= n + 1) {
       for (int i = 0; i < k; i++) getAns(table[0][i]);
       return 0;
   } 

   for (int i = 1; i < k; i++) memcpy(table[n][i], table[n][0], sizeof(table[n][0]));
   for (int i = n - 1; i >= 0; i--) {
       for (int j = n + 1 - i; j < k; j++) {
           memcpy(table[i][j], table[i + 1][j - 1], sizeof(table[i][j]));
           plus(table[i][j], table[i][j - 1]);
       }
   }

   for (int i = 0; i < k; i++) {
       getAns(table[0][i]);
   }

   /*
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < k; j++)
            print(table[i][j]);
   */

    return 0;
}

