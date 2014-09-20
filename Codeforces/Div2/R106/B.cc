#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string martian_time;
string h, m;

inline int todigit(char c)
{
    if (isdigit(c)) return c - '0';
    return c - 'A' + 10;
}

int change(string s, int base)
{
    int res = 0;
    for (int i = 0; i < s.length(); i++)
        res = res * base + todigit(s[i]);
    return res;
}

bool check(string h, string m, int base)
{
    if (change(h, base) >= 24) return false;
    if (change(m, base) >= 60) return false;
    return true;
}

int main()
{
    cin >> martian_time;
    int max_digit = 0;
    for (int i = 0, flag = 1, leading_zero = 1; i < martian_time.length(); i++) {
        if (martian_time[i] == ':') {
            flag = 0;
            leading_zero = 1;
            continue;
        }
        if (leading_zero && martian_time[i] == '0') continue;
        leading_zero = 0;
        if (flag) h += martian_time[i];
        else m += martian_time[i];
        max_digit = max(max_digit, todigit(martian_time[i]));
    }

    if (max_digit == 0 || (h.length() <= 1 && m.length() <= 1)) {
        if (h.length() == 0 || todigit(h[0]) < 24) puts("-1");
        else puts("0");
        return 0;
    }
    bool possible = check(h, m, max_digit + 1);
    if (!possible) {
        puts("0");
        return 0;
    }

    for (int i = max_digit + 1; check(h, m, i); i++)
        printf("%d\n", i);

    return 0;
}

