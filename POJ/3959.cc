/*
 *  SRC: POJ 3959
 * PROB: Alignment of Code
 * ALGO: NULL
 * DATE: Oct 05, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> code[1024];
int max_len[200];
char buf[200];

int main()
{
    int line = 0;
    while (gets(buf)) {
        string s = "";
        char *p = buf;
        while (*p && *p == ' ') p++;
        while (*p) {
            if (*p == ' ') {
                code[line].push_back(s);
                s = "";
                while (*p && *p == ' ') p++;
            }
            else s += *p++;
        }
        if (s != "") code[line].push_back(s);
        line++;
    }

    for (int i = 0; i < line; i++) {
        for (int j = 0; j < code[i].size(); j++)
            if (code[i][j].length() > max_len[j])
                max_len[j] = code[i][j].length();
    }

    for (int i = 0; i < line; i++) {
        for (int j = 0; j < code[i].size() - 1; j++) {
            printf("%s ", code[i][j].c_str());
            for (int k = code[i][j].length(); k < max_len[j]; k++) putchar(' ');
        }
        printf("%s\n", (code[i].end() - 1)->c_str());
    }

    return 0;
}
