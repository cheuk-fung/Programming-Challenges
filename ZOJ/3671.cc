#include <iostream>
#include <map>
#include <string>

using namespace std;

bool check_seven_pairs(string tiles, map<string, int> cnt)
{
    if (cnt.size() != 7) {
        return false;
    }
    for (map<string, int>::const_iterator it = cnt.begin(); it != cnt.end(); it++) {
        if (it->second != 2) {
            return false;
        }
    }

    return true;
}

bool check_thirteen_orphans(string tiles, map<string, int> cnt)
{
    if (cnt.size() != 13) {
        return false;
    }
    string thirteen_orphans = "1s9s1m9m1p9p1z2z3z4z5z6z7z";
    for (int i = 0; i < 13 << 1; i += 2) {
        string s = thirteen_orphans.substr(i, 2);
        if (!cnt.count(s)) {
            return false;
        }
    }

    return true;
}

int main()
{
    string tiles;
    while (cin >> tiles) {
        map<string, int> cnt;
        for (int i = 0; i < 14 << 1; i += 2) {
            string s = tiles.substr(i, 2);
            cnt[s]++;
        }
        if (check_seven_pairs(tiles, cnt)) {
            cout << "Seven Pairs" << endl;
        } else if (check_thirteen_orphans(tiles, cnt)) {
            cout << "Thirteen Orphans" << endl;
        } else {
            cout << "Neither!" << endl;
        }
    }

    return 0;
}
