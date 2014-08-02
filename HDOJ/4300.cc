/*
 *  SRC: HDOJ 4300
 * PROB: Clairewd’s message
 * ALGO: KMP
 * DATE: Jul 19, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>

using namespace std;

char encode[100], decode[100], s[100010];
int prn[100010];

void kmp_init(int *prn, char *b, int m)
{
    prn[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && b[j] != encode[b[i] - 'a']) j = prn[j - 1];
        if (b[j] == encode[b[i] - 'a']) j++;
        prn[i] = j;
    }
}


int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        scanf("%s%s", encode, s);
        for (int i = 0; i < 26; i++) {
            decode[encode[i] - 'a'] = i;
        }
        int len = strlen(s);
        kmp_init(prn, s, len);
        int m = prn[len - 1] - 1;
        while (m >= len / 2) m = prn[m] - 1;
        for (int i = 0; i < len; i++) putchar(s[i]);
        for (int i = m + 1, j = len; i < j - 1 - m; i++, len++) {
            putchar(decode[s[i] - 'a'] + 'a');
        }
        putchar(10);
    }

    return 0;
}
