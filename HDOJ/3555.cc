/*
 *  SRC: HDOJ 3555
 * PROB: Bomb
 * ALGO: DP
 * DATE: Oct 06, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

unsigned long long f[21][3];
/*
 * f[i][0]: length <= i, does not contain 49
 * f[i][1]: length == i, does not contain 49 and begin with 9
 * f[i][2]: length <= i, contains 49
 */

int main()
{
    ios_base::sync_with_stdio(false);

    f[0][0] = 1;
    for (int i = 1; i <= 20; i++) {
        f[i][0] = f[i - 1][0] * 10 - f[i - 1][1];
        f[i][1] = f[i - 1][0];
        f[i][2] = f[i - 1][2] * 10 + f[i - 1][1];
    }

    int tasks;
    cin >> tasks;
    while (tasks--) {
        unsigned long long n;
        cin >> n;
        n++;
        ostringstream os;
        os << n;
        string s = os.str();

        unsigned long long cnt = 0;
        bool fortynine = false;
        for (int i = 0; i < (int)s.length(); i++) {
            cnt += f[s.length() - i - 1][2] * (s[i] - '0');
            if (fortynine) {
                cnt += f[s.length() - i - 1][0] * (s[i] - '0');
            } else if (s[i] > '4') {
                cnt += f[s.length() - i - 1][1];
            }
            if (i > 0 && s[i - 1] == '4' && s[i] == '9') fortynine = true;
        }
        cout << cnt << endl;
    }

    return 0;
}

