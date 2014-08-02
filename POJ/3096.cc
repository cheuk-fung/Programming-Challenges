/*
 *  SRC: POJ 3096
 * PROB: Surprising Strings
 * ALGO: NULL
 * DATE: Mar 29, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <set>

using namespace std;

string check(string s)
{
    for (int i = 1; i < s.length(); i++) {
        set<string> substrings;
        for (int j = 0; j + i < s.length(); j++) {
            string substring = s.substr(j, 1) + s.substr(j + i, 1);
            if (substrings.count(substring)) {
                return " NOT";
            }
            substrings.insert(substring);
        }
    }

    return "";
}

int main()
{
    while (true) {
        string s;
        cin >> s;
        if (s == "*") break;
        cout << s << " is" << check(s) << " surprising." << endl;
    }

    return 0;
}

