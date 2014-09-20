#include <vector>
#include <string>

using namespace std;

const int INF = 0x7fffffff;
const long long LLINF = 0x3f3f3f3f3f3f3f3fll;

class ImportantSequence {
    private:

    public:
        int getCount(vector <int> B, string operators)
        {
            long long low = 1, high = LLINF;
            long long ans = LLINF;
            for (int i = 0; i < B.size(); i++) {
                long long t_low = low, t_high = high;
                if (operators[i] == '+') {
                    low = -t_high + B[i];
                    if (low < 1) low = 1;
                    high = -t_low + B[i];
                    if (high <= 0) return 0;
                } else {
                    low = t_low - B[i];
                    if (low < 1) low = 1;
                    high = t_high - B[i];
                    if (high <= 0) return 0;
                }
                ans = min(ans, high);
            }

            return ans > INF ? -1 : ans;
        }
};
