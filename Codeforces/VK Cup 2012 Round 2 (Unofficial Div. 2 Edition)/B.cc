#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#define debug(x) if (DEBUG) cerr << #x << " = " << (x) << endl

#define debug_line(a, n) do {                                                \
    if (DEBUG) {                                                             \
        cerr << #a << "[" << #n << "]:" << endl;                             \
        for (int i = 0; i < (n); i++) cerr << (a)[i] << " ";                 \
        cerr << endl;                                                        \
    }                                                                        \
} while (0)

#define debug_mat(a, n, m) do {                                              \
    if (DEBUG) {                                                             \
        cerr << #a << "[" << #n << "][" << #m "]:" << endl;                  \
        for (int i = 0; i < (n); i++) {                                      \
            for (int j = 0; j < (m); j++) cerr << (a)[i][j] << " ";          \
            cerr << endl;                                                    \
        }                                                                    \
    }                                                                        \
} while(0)

typedef pair<int, int> pii;
typedef vector<int>::const_iterator vci;
typedef map<int, int>::const_iterator mci;

const int INF = 0x3f3f3f3f;
const double DINF = 1e20;
const double pi = acos(-1.0);
const double eps = 1e-6;

template<class T> inline T sqr(T x) { return x * x; }

string a, s;
int cnt[10];

int main()
{
    while (cin >> a >> s) {
        int n = a.length();
        int m = s.length();

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < m; i++) {
            cnt[s[i] - '0']++;
        }

        for (int i = 0, j = 9; i < n; i++) {
            while (cnt[j] == 0) {
                j--;
                if (j < 0) break;
            }
            if (j < 0) break;

            if (a[i] < j + '0') {
                a[i] = j + '0';
                cnt[j]--;
            }
        }

        cout << a << endl;
    }

    return 0;
}

