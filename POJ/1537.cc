/*
 *  SRC: POJ 1537
 * PROB: Identifying Legal Pascal Real Constants
 * ALGO: string
 * DATE: Jul 27, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool solve(string s)
{
    size_t pos = 0;
    if (s[pos] == '+' || s[pos] == '-') {
        pos++;
        if (pos == s.length()) return false;
    }
    if (!isdigit(s[pos])) return false;
    while (pos < s.length() && isdigit(s[pos])) pos++;
    if (pos == s.length()) return false;
    if (s[pos] == '.') {
        pos++;
        if (pos == s.length()) return false;
        if (!isdigit(s[pos])) return false;
        while (pos < s.length() && isdigit(s[pos])) pos++;
        if (pos == s.length()) return true;
    }
    if (s[pos] != 'e' && s[pos] != 'E') return false;
    pos++;
    if (s[pos] == '+' || s[pos] == '-') {
        pos++;
        if (pos == s.length()) return false;
    }
    if (!isdigit(s[pos])) return false;
    while (pos < s.length() && isdigit(s[pos])) pos++;
    if (pos == s.length()) return true;
    return false;
}

int main()
{
    string s;
    while (cin >> s, s[0] != '*') {
        cout << s << " is " << (solve(s) ? "" : "il" ) << "legal." << endl;
    }

    return 0;
}
