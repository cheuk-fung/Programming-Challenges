/*
 *  SRC: POJ 1684
 * PROB: Dynamic Declaration Language (DDL)
 * ALGO: String
 * DATE: Jul 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstring>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const int NO_ASSIGN = 0x3f3f3f3f;
const int FIRST_ASSIGN = NO_ASSIGN - 1;

int var[256];

int getnum(string s, int pos)
{
    int r = 0;
    while (isdigit(s[pos])) {
        r = r * 10 + s[pos++] - '0';
    }
    return r;
}

string line[111];

int main()
{
    int tasks;
    cin >> tasks;
    for (int task  = 1; task <= tasks; task++) {
        memset(var, 0x3f, sizeof(var));
        cout << task << endl;

        int n;
        cin >> n;
        for (int i = 0; i <= n; i++) getline(cin, line[i]);
        for (int i = 1; i < n; i++) {
            string s = line[i];

            int pos = 0;
            while (s[pos] == ' ') pos++;
            if (s[pos + 1] != ' ') {
                string key;
                key = key + (char)toupper(s[pos]) + (char)toupper(s[pos + 1]) + (char)toupper(s[pos + 2]);
                pos += 3;
                if (s[pos] != ' ') key += s[pos++];
                while (s[pos] == ' ') pos++;

                if (key == "DCL") {
                    int id = s[pos];
                    if (var[id] == FIRST_ASSIGN) {
                        cout << i << ' ' << 1 << endl;
                    } else {
                        var[id] = FIRST_ASSIGN;
                    }
                } else if (key == "GOTO") {
                    if (isalpha(s[pos])) {
                        int id = s[pos++];
                        if (var[id] == FIRST_ASSIGN) var[id] = 0;
                        if (var[id] == NO_ASSIGN) {
                            cout << i << ' ' << 2 << endl;
                            continue;
                        }
                        if (var[id] == 0) continue;
                        while (s[pos] == ' ') pos++;
                    }
                    i = getnum(s, pos) - 1;
                } else {
                    int id = s[pos++];
                    if (var[id] == NO_ASSIGN) {
                        cout << i << ' ' << 2 << endl;
                        continue;
                    }
                    if (var[id] == FIRST_ASSIGN) var[id] = 0;
                    if (key == "INC") var[id]++;
                    else var[id]--;
                }
            } else {
                int id = s[pos++];
                if (var[id] == NO_ASSIGN) {
                    cout << i << ' ' << 2 << endl;
                    continue;
                }

                while (s[pos] == ' ') pos++;
                pos++;
                while (s[pos] == ' ') pos++;
                var[id] = getnum(s, pos);
            }
        }
    }

    return 0;
}

