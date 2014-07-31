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
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;
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

bool f[50][1024];

class XorTravelingSalesman {
    private:

    public:
        int maxProfit(vector <int> cityValues, vector <string> roads)
        {
            memset(f, false, sizeof f);
            int n = SIZE(cityValues);
            queue<int> que;
            que.push(cityValues[0] * n);
            f[0][cityValues[0]] = true;
            int ans = 0;
            while (!que.empty()) {
                int u = que.front() % n, v = que.front() / n;
                ans = max(ans, v);
                que.pop();
                for (int i = 0; i < n; i++) {
                    if (roads[u][i] == 'Y') {
                        if (!f[i][v ^ cityValues[i]]) {
                            f[i][v ^ cityValues[i]] = true;
                            que.push((v ^ cityValues[i]) * n + i);
                        }
                    }
                }
            }
            return ans;
        }
};

// BEGIN CUT HERE
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) 
	{
		cout << "Testing XorTravelingSalesman (250.0 points)" << endl << endl;
		for (int i = 0; i < 20; i++)
		{
			ostringstream s; s << argv[0] << " " << i;
			int exitCode = system(s.str().c_str());
			if (exitCode)
				cout << "#" << i << ": Runtime Error" << endl;
		}
		int T = time(NULL)-1347585023;
		double PT = T/60.0, TT = 75.0;
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		cout << endl;
		cout << "Time  : " << T/60 << " minutes " << T%60 << " secs" << endl;
		cout << "Score : " << 250.0*(.3+(.7*TT*TT)/(10.0*PT*PT+TT*TT)) << " points" << endl;
	}
	else
	{
		int _tc; istringstream(argv[1]) >> _tc;
		XorTravelingSalesman _obj;
		int _expected, _received;
		time_t _start = clock();
		switch (_tc)
		{
			case 0:
			{
				int cityValues[] = {0, 7, 11, 5, 2};
				string roads[] = {"NYNYY",
				                  "YNYNN",
				                  "NYNNN",
				                  "YNNNN",
				                  "YNNNN"};
				_expected = 14;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}
			case 1:
			{
				int cityValues[] = {556};
				string roads[] = {"N"};
				_expected = 556;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}
			case 2:
			{
				int cityValues[] = {0, 4, 8, 32, 512};
				string roads[] = {"NYYYY",
				                  "YNNNN",
				                  "YNNNN",
				                  "YNNNN",
				                  "YNNNN"};
				_expected = 556;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}
			case 3:
			{
				int cityValues[] = {37, 1, 19, 64, 42, 41, 64, 64, 54, 16, 256, 36, 64, 2, 4, 2, 62, 29, 58, 64, 1, 32, 16,
				                    256, 17, 2, 17, 4, 1, 64, 21, 8, 256, 63, 3, 1, 43, 15, 8, 39, 41, 8, 16, 8, 16, 256, 64, 512, 45, 64};
				string roads[] = {"NNNNNNYYYYNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN",
				                  "NNNNNNNNNNNNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNYYNNNYYNN",
				                  "NNNNNYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
				                  "NNNNNNNYNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
				                  "NNNNNNNNNNNNNNNYNNYNYNNNNNNYNNNNNNNNNNYNNNNNNNNNNN",
				                  "NNYNNNYNNNNNNNNYNNYNNNYYNNNYNYNNNNYNNNNNNNNYNNNNNN",
				                  "YNYNNYNYNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNNNNNYNNYNN",
				                  "YNNYNNYNYNYYNNNNNNNNNNNNNNNNNNNNNNYNNYNNNNNNNNNNNN",
				                  "YNNNNNNYNNNNNNNNNNNNNNYNYNNNNNNNNNNYYYNNNNNNNYNNNY",
				                  "YNNNNNNNNNNNNNNNNYNYNYNYYNNNYNNNNYNNNNNNNNNNNNNNNY",
				                  "NNNNNNNYNNNNYNNNNNNNNYYNNNYYNNNNYNYYNNNNNNNNNNNNNN",
				                  "NNNNNNNYNNNNNNYNNNNYYNNNYNNYYNNNNNNNNNNNNNYNYNNNNN",
				                  "NNNNNNNNNNYNNNNNYNNNNYNNNNNNNNNNYNYNNYNYNNNYNYNNNN",
				                  "NNNNNNNNNNNNNNNYNNNNNNNNNYNNNNNNNNNNNNYNNNNNNNNYNN",
				                  "NNNNNNNNNNNYNNNNNYNYNNYYNNNNNYNNNNNNNNNYNNYNNYNNNN",
				                  "NNNNYYYNNNNNNYNNNYYNNYNNNYNYYNNNNNNNNNYYYNNYNNYNYN",
				                  "NYNNNNNNNNNNYNNNNNNNYNNNYYNNNYNNNNYNNNNNNNNNNNNNNN",
				                  "NNNNNNNNNYNNNNYYNNNNNNYNNNYNNNNNYNNYNYYNNNNYNNNYNN",
				                  "NNNYYYNNNNNNNNNYNNNNNYNYNYNNNNNNNNYNNNNNNNNNNNNNNN",
				                  "NNNNNNNNNYNYNNYNNNNNNYNYYYNNNNNNNNNNNYNNYNNNNNYNNN",
				                  "NNNNYNNNNNNYNNNNYNNNNYNNNYYNNNYNNNYNNNNNNNNNNYNYNY",
				                  "NNNNNNNNNYYNYNNYNNYYYNYNNNNNNNNYNYNNNNNNNNNNYNNNNN",
				                  "NNNNNYNNYNYNNNYNNYNNNYNNNNNNNNNNNYNNYNYNNYNNNNNNNN",
				                  "NNNNNYNNNYNNNNYNNNYYNNNNNNNNNNNNNNNNNNNNNNYNNNYNNN",
				                  "NYNNNNNNYYNYNNNNYNNYNNNNNNNNNNYNNNNNNYNNNYNNYNNNNN",
				                  "NNNNNNNNNNNNNYNYYNYYYNNNNNNYNNNNNNNNNNNYYNNNNNNNYN",
				                  "NNNNNNNNNNYNNNNNNYNNYNNNNNNNNYNNNNYNNNNNNYYNNNNYNN",
				                  "NNNNYYNNNNYYNNNYNNNNNNNNNYNNNYYNYNNNNNNNNNNNNNNNNN",
				                  "NNNNNNNNNYNYNNNYNNNNNNNNNNNNNYNNNNYNNNNNNNNYNNYNYN",
				                  "NNNNNYNNNNNNNNYNYNNNNNNNNNYYYNNNNNNNNYNNNNYNNNNNNN",
				                  "NNNNNNNNNNNNNNNNNNNNYNNNYNNYNNNNNYNNNNNNNNNNNNNNNY",
				                  "NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNYNNNNNNN",
				                  "NNNNNNNNNNYNYNNNNYNNNNNNNNNYNNNYNNNYYNNNNNYNNNYNNN",
				                  "NNNNNNNNNYNNNNNNNNNNNYYNNNNNNNYNNNNNNNYNNYNNNNNNNN",
				                  "NNNNNYNYNNYNYNNNYNYNYNNNNNYNYNNNNNNYYNYNYNYNNNNNYN",
				                  "YNNNNNYNYNYNNNNNNYNNNNNNNNNNNNNNYNYNNNNNYNNYNNNYNN",
				                  "NNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNYNYNNNNNNYNNNNNNYN",
				                  "NNNNNNNYYNNNYNNNNYNYNNNNYNNNNYNNNNNNNNNNNYNNNNYNNN",
				                  "NNNNYNNNNNNNNYNYNYNNNNYNNNNNNNNNNYYNNNNYNNNNNNNNNY",
				                  "NNNNNNNNNNNNYNYYNNNNNNNNNYNNNNNNNNNNNNYNNNNNYNYYNN",
				                  "NNNNNNNNNNNNNNNYNNNYNNNNNYNNNNNNNNYYNNNNNNNNNNNNNN",
				                  "NYNNNNNNNNNNNNNNNNNNNNYNYNYNNNNNNYNNYYNNNNNNNNNNNN",
				                  "NYNNNNNNNNNYNNYNNNNNNNNYNNYNNYNYYNYNNNNNNNNNYNNNNN",
				                  "NNNNNYNNNNNNYNNYNYNNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNY",
				                  "NNNNNNYNNNNYNNNNNNNNNYNNYNNNNNNNNNNNNNNYNNYNNYNNNY",
				                  "NNNNNNNNYNNNYNYNNNNNYNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
				                  "NYNNNNNNNNNNNNNYNNNYNNNYNNNNYNNNYNNNNYNYNNNNNNNNNN",
				                  "NYNNNNYNNNNNNYNNNYNNYNNNNNYNNNNNNNNYNNNYNNNNNNNNNN",
				                  "NNNNNNNNNNNNNNNYNNNNNNNNNYNNYNNNNNYNYNNNNNNNNNNNNN",
				                  "NNNNNNNNYYNNNNNNNNNNYNNNNNNNNNYNNNNNNNYNNNNYYNNNNN"};
				_expected = 895;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}
			/*case 4:
			{
				int cityValues[] = ;
				string roads[] = ;
				_expected = ;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}*/
			/*case 5:
			{
				int cityValues[] = ;
				string roads[] = ;
				_expected = ;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}*/
			/*case 6:
			{
				int cityValues[] = ;
				string roads[] = ;
				_expected = ;
				_received = _obj.maxProfit(vector <int>(cityValues, cityValues+sizeof(cityValues)/sizeof(int)), vector <string>(roads, roads+sizeof(roads)/sizeof(string))); break;
			}*/
			default: return 0;
		}
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		double _elapsed = (double)(clock()-_start)/CLOCKS_PER_SEC;
		if (_received == _expected)
			cout << "#" << _tc << ": Passed (" << _elapsed << " secs)" << endl;
		else
		{
			cout << "#" << _tc << ": Failed (" << _elapsed << " secs)" << endl;
			cout << "           Expected: " << _expected << endl;
			cout << "           Received: " << _received << endl;
		}
	}
}

// END CUT HERE
