/*
 *  SRC: ZOJ 3501
 * PROB: Roman Order
 * ALGO: NULL
 * DATE: Oct 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const string Roman[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"","C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM"}
};

struct Number {
    char a[10];
    string s;

    bool operator<(const Number &o) const { return s < o.s; }
} num[10010];

int main()
{
    int tasks;
    scanf("%d", &tasks);
    while (tasks--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%s", num[i].a);
            num[i].s = "";
            for (int j = strlen(num[i].a) - 1, k = 0; j >= 0; j--, k++) {
                num[i].s = Roman[k][num[i].a[j] - '0'] + num[i].s;
            }
        }

        sort(num, num + n);
        for (int i = 0; i < n; i++) {
            printf("%s%c", num[i].a, i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}

