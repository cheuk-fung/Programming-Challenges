/*
 *  SRC: ZOJ 3490
 * PROB: String Successor
 * ALGO: String
 * DATE: Oct 04, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

enum {
    NOTYPE = 0,
    DIGIT = '1',
    UPPER = 'A',
    LOWER = 'a'
};

char s[200];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        memset(s, 0, sizeof s);

        int n;
        scanf(" %s%d", s, &n);
        int len = strlen(s);
        reverse(s, s + len);
        for (int i = 0; i < n; i++) {
            int lasttype = NOTYPE;
            int lastpos = -1;
            for (int j = 0; ; j++) {
                while (s[j] && !isalnum(s[j])) j++;
                if (!s[j]) {
                    if (lasttype == NOTYPE) {
                        s[0]++;
                    } else {
                        for (int k = j; k > lastpos; k--) s[k] = s[k - 1];
                        s[lastpos] = lasttype;
                        len++;
                    }
                    break;
                }

                lastpos = j + 1;
                if (isdigit(s[j])) {
                    lasttype = DIGIT;
                    if (s[j] < '9') {
                        s[j]++;
                        break;
                    } else {
                        s[j] = '0';
                    }
                } else if (isupper(s[j])) {
                    lasttype = UPPER;
                    if (s[j] < 'Z') {
                        s[j]++;
                        break;
                    } else {
                        s[j] = 'A';
                    }
                } else {
                    lasttype = LOWER;
                    if (s[j] < 'z') {
                        s[j]++;
                        break;
                    } else {
                        s[j] = 'a';
                    }
                }
            }

            for (int j = len - 1; j >= 0; j--) putchar(s[j]);
            putchar(10);
        }

        putchar(10);
    }

    return 0;
}

