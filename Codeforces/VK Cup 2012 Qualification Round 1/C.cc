#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> dir;

void walk(string cmd)
{
    if (cmd == "") return ;

    if (cmd[0] == '.') {
        dir.pop_back();
        if (cmd == "..") return ;
        return walk(cmd.substr(3));
    }

    int pos = 0;
    while (isalpha(cmd[pos])) pos++;
    dir.push_back(cmd.substr(0, pos));
    if (pos != cmd.size())
        walk(cmd.substr(pos + 1));
}

int main()
{
    int n;
    string cmd;

    cin >> n;
    while (n--) {
        cin >> cmd;
        if (cmd == "pwd") {
            cout << "/";
            for (int i = 0; i < dir.size(); i++)
                cout << dir[i] << "/";
            cout << endl;
        }
        else {
            cin >> cmd;
            if (cmd[0] == '/') {
                dir.clear();
                cmd = cmd.substr(1);
            }
            walk(cmd);
        }
    }

    return 0;
}

