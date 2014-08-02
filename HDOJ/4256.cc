/*
 *  SRC: HDOJ 4256
 * PROB: The Famous Clock
 * ALGO: NULL
 * DATE: Jul 17, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> roman;

int main()
{
    roman["I"] = 1;
    roman["II"] = 2;
    roman["III"] = 3;
    roman["IV"] = 4;
    roman["V"] = 5;
    roman["VI"] = 6;
    roman["VII"] = 7;
    roman["VIII"] = 8;
    roman["IX"] = 9;
    roman["X"] = 10;
    roman["XI"] = 11;
    roman["XII"] = 12;

    int task = 1;
    string s;
    while (cin >> s) cout << "Case " << task++ << ": " << roman[s] << endl;

    return 0;
}

