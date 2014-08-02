/*
 *  SRC: NKOJ p1579
 * PROB: Maya Calendar
 * ALGO: NULL
 * DATE: Nov 27, 2010
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

string SHaabMonth[19] = {
    "pop", "no", "zip", "zotz", "tzec", "xul",
    "yoxkin", "mol", "chen", "yax", "zac", "ceh",
    "mac", "kankin", "muan", "pax", "koyab", "cumhu",
    "uayet"
};

string STzolkinDay[20] = {
    "imix", "ik", "akbal", "kan", "chicchan",
    "cimi", "manik", "lamat", "muluk", "ok",
    "chuen", "eb", "ben", "ix", "mem",
    "cib", "caban", "eznab", "canac", "ahau"
};

map<string, int> HaabMonth;

inline void init()
{
    for (int i = 0; i < 19; i++) HaabMonth[SHaabMonth[i]] = i;
}


struct HaabDate {
    int d, m, y;

    HaabDate() {
	cin >> d;
	cin.get();
	string s;
	cin >> s >> y;
	m = HaabMonth[s];
    }
};

struct TzolkinDate {
    int d, n, y;

    ~TzolkinDate() {
	cout << d << ' ' << STzolkinDay[n] << ' ' << y << '\n';
    }
};

inline void convert()
{
    HaabDate Haab;
    TzolkinDate Tzolkin;

    int totalDay = Haab.d + Haab.m * 20 + Haab.y * 365;

    Tzolkin.d = (totalDay + 1) % 13;
    if (!Tzolkin.d) Tzolkin.d = 13;
    Tzolkin.n = totalDay % 20;
    Tzolkin.y = totalDay / (13 * 20);
}

int main()
{
    init();
    int n;
    cin >> n;
    cout << n << '\n';
    while (n--) convert();

    return 0;
}

