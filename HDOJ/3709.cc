/*
 *  SRC: HDOJ 3709
 * PROB: Balanced Number
 * ALGO: DP
 * DATE: Oct 07, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

string s;
long long f[20][20][2000];

long long dp(int pos, int pivot, int torques, bool limit)
{
    if (pos == (int)s.length()) return !limit && torques == 0;
    if (torques < 0) return 0;
    if (!limit && f[pos][pivot][torques] != -1) return f[pos][pivot][torques];

    long long res = 0;
    int upper = limit ? s[pos] - '0' : 10;
    for (int i = 0; i < upper; i++) {
        res += dp(pos + 1, pivot, torques + i * (pivot - pos), false);
    }
    if (limit) res += dp(pos + 1, pivot, torques + upper * (pivot - pos), true);
    else f[pos][pivot][torques] = res;

    return res;
}

long long calc(long long n)
{
    ostringstream os;
    os << n;
    s = os.str();

    memset(f, 0xff, sizeof f);
    long long res = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        res += dp(0, i, 0, true);
    }
    res -= s.length() - 1;

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int tasks;
    cin >> tasks;
    while (tasks--) {
        long long x, y;
        cin >> x >> y;
        long long lres = calc(x);
        long long rres = calc(y + 1);
        cout << (rres - lres) << endl;
    }

    return 0;
}

