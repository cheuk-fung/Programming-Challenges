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

class PasswordXPalindrome {
    private:

    public:
        int minSwaps(string password)
        {
            int one_cnt = 0;
            int vis[26];
            memset(vis, 0, sizeof(vis));
            for (int i = 0; i < password.length(); i++) {
                vis[password[i] - 'a']++;
            }
            for (int i = 0; i < 26; i++) {
                if (vis[i] == 1) {
                    if (one_cnt) return -1;
                    one_cnt = 1;
                }
            }

            int cnt = 0;
            for (int i = 0, j = password.length() - 1; i < password.length() / 2; i++, j--) {
                if (password[i] != password[j]) {
                    cnt++;
                    for (int k = i + 1; k < j; k++) {
                        if (password[k] == password[i]) {
                            swap(password[k], password[j]);
                            break;
                        }
                    }
                }
            }

            return cnt;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "levle"; int Arg1 = 1; verify_case(0, Arg1, minSwaps(Arg0)); }
	void test_case_1() { string Arg0 = "racecar"; int Arg1 = 0; verify_case(1, Arg1, minSwaps(Arg0)); }
	void test_case_2() { string Arg0 = "abcdadcb"; int Arg1 = 3; verify_case(2, Arg1, minSwaps(Arg0)); }
	void test_case_3() { string Arg0 = "msmscielciel"; int Arg1 = 5; verify_case(3, Arg1, minSwaps(Arg0)); }
	void test_case_4() { string Arg0 = "hicanyouguesstodaywriter"; int Arg1 = -1; verify_case(4, Arg1, minSwaps(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    PasswordXPalindrome ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE 
