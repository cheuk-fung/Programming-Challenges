/*
 *  SRC: HDOJ 4245
 * PROB: A Famous Music Composer
 * ALGO: NULL
 * DATE: Jul 16, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

map<string, string> alternate;

int main()
{
    alternate["A#"] = "Bb";
    alternate["Bb"] = "A#";
    alternate["C#"] = "Db";
    alternate["Db"] = "C#";
    alternate["D#"] = "Eb";
    alternate["Eb"] = "D#";
    alternate["F#"] = "Gb";
    alternate["Gb"] = "F#";
    alternate["G#"] = "Ab";
    alternate["Ab"] = "G#";

    int task = 1;
    string s, t;
    while (cin >> s >> t) {
        cout << "Case " << task++ << ": ";

        string r;
        if (alternate.count(s)) {
            r = alternate[s] + " " + t;
            cout << r << endl;
        } else {
            cout << "UNIQUE" << endl;
        }
    }

    return 0;
}

