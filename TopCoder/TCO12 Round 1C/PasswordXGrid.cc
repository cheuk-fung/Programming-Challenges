#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
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
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
const double DINF = 1e20;
const double pi = acos(-1.0);
const double eps = 1e-6;

template<class T> inline T sqr(T x) { return x * x; }

class PasswordXGrid {
    private:

    public:
        int minSum(vector <string> horizontal, vector <string> vertical)
        {
            int f[100][100];
            memset(f, 0, sizeof(f));
            for (int i = 0; i < horizontal.size(); i++) {
                for (int j = 0; j < vertical[0].length(); j++) {
                    if (i > 0) {
                        f[i][j] = f[i - 1][j] + vertical[i - 1][j] - '0';
                    }
                    if (j > 0) {
                        f[i][j] = max(f[i][j], f[i][j - 1] + horizontal[i][j - 1] - '0');
                    }
                }
            }

            return f[horizontal.size() - 1][vertical[0].length() - 1];
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1","4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"32"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, minSum(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"47", "59"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"361"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 19; verify_case(1, Arg2, minSum(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"36", "23", "49"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"890", "176"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 28; verify_case(2, Arg2, minSum(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"8888585","5888585"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"58585858"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 58; verify_case(3, Arg2, minSum(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"7777777","7777777","7777777","7777777"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"44444444","44444444","44444444"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 61; verify_case(4, Arg2, minSum(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    PasswordXGrid ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE 
