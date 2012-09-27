#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <functional>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <cassert>

using namespace std;

#ifndef LEEWINGS_DEBUG
#define LEEWINGS_DEBUG 0
#endif

#define debug(x) if (LEEWINGS_DEBUG) cerr << #x << " = " << (x) << endl

#define debug_line(a, n) do {                                                \
    if (LEEWINGS_DEBUG) {                                                    \
        cerr << #a << "[" << #n << "]:" << endl;                             \
        for (int i = 0; i < (n); i++) cerr << (a)[i] << " ";                 \
        cerr << endl;                                                        \
    }                                                                        \
} while (0)

#define debug_mat(a, n, m) do {                                              \
    if (LEEWINGS_DEBUG) {                                                    \
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
const int NEGINF = 0xc0c0c0c0;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const long long NEGLLINF = 0xc0c0c0c0c0c0c0c0ll;
const double DINF = 1.0/0.0f;
const double pi = acos(-1.0);
const double eps = 1e-8;
const int MOD = 1000000007;

inline int LC(int x) { return x << 1; }
inline int RC(int x) { return (x << 1) | 1; }
inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline bool greq(double x, double y) { return x + eps >= y; }
inline bool lseq(double x, double y) { return x - eps <= y; }
inline double fmax(double x, double y) { return gr(x, y) ? x : y; }
inline double fmin(double x, double y) { return ls(x, y) ? x : y; }

template<class T> inline T SQR(T x) { return x * x; }
template<class T> inline int SIZE(const T &x) { return x.size(); }

int main()
{
    int a[4];
    for (int i = 0; i < 4; i++) cin >> a[i];
    sort(a, a + 4);
    cout << (4 - (unique(a, a + 4) - a)) << endl;



    return 0;
}

