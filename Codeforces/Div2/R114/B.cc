#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;
vector<string> output;
vector<bool> sharps;

int main()
{
    while (cin) {
        string line;
        getline(cin, line);
        lines.push_back(line);
        sharps.push_back(false);
    }
    lines.pop_back();
    sharps.pop_back();

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            if (lines[i][j] == ' ') continue;
            if (lines[i][j] == '#') {
                sharps[i] = true;
            }
            break;
        }
    }


    bool newone = true;
    for (int i = 0; i < lines.size(); i++) {
        if (sharps[i]) {
            output.push_back(lines[i]);
            newone = true;
        } else {
            string s = "";
            for (int j = 0; j < lines[i].length(); j++) {
                if (lines[i][j] != ' ') {
                    s += lines[i][j];
                }
            }
            if (newone) {
                output.push_back(s);
                newone = false;
            } else {
                output[output.size() - 1] += s;
            }
        }
    }

    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << endl;
    }

    return 0;
}

