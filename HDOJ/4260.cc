/*
 *  SRC: HDOJ 4260
 * PROB: The End of The World
 * ALGO: Math
 * DATE: Aug 25, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>

int main()
{
    char s[100];
    while (scanf("%s", s), s[0] != 'X') {
        int len = strlen(s);
        char now = 'A';

        unsigned long long cnt = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (s[i] != now) {
                cnt += 1ull << i;
                if (now != 'A' && s[i] != 'A') now = 'A';
                else if (now != 'B' && s[i] != 'B') now = 'B';
                else now = 'C';
            }
        }

        unsigned long long ans = (1ull << len) - 1 - cnt;
        printf("%I64d\n", (long long)ans);
    }

    return 0;
}

