/*
 *  SRC: POJ 2503
 * PROB: Babelfish
 * ALGO: Hash
 * DATE: Mar 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cctype>
#include <string>
#include <map>

using std::string;
using std::map;

map<string, string> dict;

int main()
{
    while (true) {
        char c = getchar();
        if (c == '\n') break;
        string s = "", t = "";
        s += c;
        while (!isspace(c = getchar())) s += c;
        while (!isspace(c = getchar())) t += c;
        dict[t] = s;
    }

    char buf[20];
    while (gets(buf)) {
        string word = buf;
        if (dict.count(word))
            printf("%s\n", dict[word].c_str());
        else puts("eh");
    }

    return 0;
}

