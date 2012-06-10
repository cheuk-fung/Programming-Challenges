#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

vector<string> line;

int get_non_space(string s)
{
    for (int i = 0; i < s.length(); i++) {
        if (!isspace(s[i])) {
            return i;
        }
    }

    return s.length();
}

string proc(int n)
{
    int x = 0, throw_x = INF;
    string throw_var = "";
    for (int now = 0; now < n; now++) {
        int pos;
        while (now < n && (pos = get_non_space(line[now])) == line[now].length()) now++;
        if (now == n) break;

        string s = line[now];
        if (s[pos] == 't' && s[pos + 1] == 'r') {
            x++;
        } else if (s[pos] == 't') {
            while (s[pos] != '(') pos++;
            pos++;
            while (isspace(s[pos])) pos++;
            while (!isspace(s[pos]) && s[pos] != ')') throw_var += s[pos++];
            throw_x = x - 1;
        } else if (--x == throw_x) {
            throw_x = x - 1;

            while (s[pos] != '(') pos++;
            pos++;
            while (isspace(s[pos])) pos++;

            string t = "";
            while (!isspace(s[pos]) && s[pos] != ',') t += s[pos++];

            if (t == throw_var) {
                string ans = "";
                while (s[pos] != '"') pos++;
                pos++;
                while (s[pos] != '"') ans += s[pos++];
                return ans;
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

