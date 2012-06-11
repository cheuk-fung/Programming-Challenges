#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

vector<string> line;

string proc(int n)
{
    int x = 0, throw_x = INF;
    string throw_var;
    for (int i = 0; i < n; i++) {
        if (line[i].find("(") != string::npos) line[i].replace(line[i].find("("), 1, " ");
        if (line[i].find(")") != string::npos) line[i].replace(line[i].rfind(")"), 1, " ");
        if (line[i].find(",") != string::npos) line[i].replace(line[i].find(","), 1, " ");
        istringstream token(line[i]);

        string expr;
        token >> expr;
        if (expr == "try") {
            x++;
        } else if (expr == "throw") {
            token >> throw_var;
            throw_x = x - 1;
        } else if (expr == "catch" && --x == throw_x) {
            throw_x = x - 1;

            string var;
            token >> var;
            if (var == throw_var) {
                line[i].erase(0, line[i].find("\"") + 1);
                line[i].erase(line[i].rfind("\""));
                return line[i];
            }
        }
    }

    return "Unhandled Exception";
}

int main()
{
    int n;
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++) {
        string str;
        getline(cin, str);
        line.push_back(str);
    }

    cout << proc(n) << endl;

    return 0;
}

