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

class PasswordXGuessing {
    private:
        bool check(const string &word, const vector<string> &guesses)
        {
            for (int i = 1; i < guesses.size(); i++) {
                bool one_diff = false;
                for (int j = 0; j < word.length(); j++) {
                    if (guesses[i][j] != word[j]) {
                        if (one_diff) {
                            return false;
                        }
                        one_diff = true;
                    }
                }
                if (!one_diff) {
                    return false;
                }
            }

            return true;
        }

    public:
        long long howMany(vector <string> guesses)
        {
            int cnt = 0;
            for (int i = 0; i < guesses[0].length(); i++) {
                for (int j = '0'; j <= '9'; j++) {
                    if (j == guesses[0][i]) continue;
                    string word = guesses[0];
                    word[i] = j;
                    if (check(word, guesses)) {
                        cnt++;
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
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arr0[] = {"58", "47"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, howMany(Arg0)); }
        void test_case_1() { string Arr0[] = {"539", "540", "541"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(1, Arg1, howMany(Arg0)); }
        void test_case_2() { string Arr0[] = {"12", "34", "56", "78"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, howMany(Arg0)); }
        void test_case_3() { string Arr0[] = {"2", "3", "5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 7LL; verify_case(3, Arg1, howMany(Arg0)); }
        void test_case_4() { string Arr0[] = {"4747", "4747", "4747", "4747"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 36LL; verify_case(4, Arg1, howMany(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    PasswordXGuessing ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE 
