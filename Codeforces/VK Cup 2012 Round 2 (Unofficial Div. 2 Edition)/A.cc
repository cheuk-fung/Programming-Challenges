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

int main()
{
    int n, a, b;
    int h[2011];
    while (cin >> n >> a >> b) {
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        sort(h, h + n);
        cout << h[b] - h[b - 1] << endl;
    }

    return 0;
}

