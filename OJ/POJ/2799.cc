/*
 *  SRC: POJ 2799
 * PROB: IP Networks
 * ALGO: NULL
 * DATE: Aug 25, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>

int n;
int ip[1000][4];
char ip_str[100];
char* s;

int next_int()
{
    int res = 0;
    while (*s && *s != '.')
        res = res * 10 + *s++ - '0';
    s++;
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", ip_str);
        s = ip_str;
        for (int j = 0; j < 4; j++)
            ip[i][j] = next_int();

    }

    int min_len = 32;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int curr_len = 0;
            for (int k = 0; k < 4; k++) {
                if (ip[i][k] == ip[j][k]) curr_len += 8;
                else {
                    for (int x = 128; x > 0; x >>= 1) {
                        if ((ip[i][k] & x) == (ip[j][k] & x)) curr_len++;
                        else break;
                    }
                    break;
                }
            }
            if (curr_len < min_len) min_len = curr_len;
        }
    }

    int pos = 0, len = 32 - min_len;
    if (min_len >= 8) {
        printf("%d.", ip[0][0]);
        min_len -= 8;
        pos++;
    }
    if (min_len >= 8) {
        printf("%d.", ip[0][1]);
        min_len -= 8;
        pos++;
    }
    if (min_len >= 8) {
        printf("%d.", ip[0][2]);
        min_len -= 8;
        pos++;
    }
    min_len = 8 - min_len;
    printf("%d", ip[0][pos] >> min_len << min_len);
    while (++pos < 4) printf(".0");
    putchar(10);

    if (len <= 8)
        printf("255.255.255.%d\n", 256 - (1 << len));
    else if (len <= 16)
        printf("255.255.%d.0\n", 256 - (1 << (len - 8)));
    else if (len <= 24)
        printf("255.%d.0.0\n", 256 - (1 << (len - 16)));
    else
        printf("%d.0.0.0\n", 256 - (1 << (len - 24)));

    return 0;
}
