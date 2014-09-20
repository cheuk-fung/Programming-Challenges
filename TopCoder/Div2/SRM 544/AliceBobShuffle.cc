#include <cstring>
#include <vector>

using namespace std;

const int MOD = 1000000007;
long long f[51][51][101];

class AliceBobShuffle {
    private:
        void add(long long &a, long long b) { a = (a + b) % MOD; }

    public:
        int countWays(vector <int> AliceStart, vector <int> BobStart, vector <int> AliceEnd, vector <int> BobEnd)
        {
            if (AliceStart.size() + BobStart.size() != AliceEnd.size() + BobEnd.size()) return 0;
            memset(f, 0, sizeof(f));
            f[0][0][0] = 1;
            for (int i = 0; i <= AliceStart.size(); i++) {
                for (int j = 0; j <= BobStart.size(); j++) {
                    for (int k = 0; k <= AliceEnd.size(); k++) {
                        int l = i + j - k;
                        if (l < 0) break;
                        if (i > 0 && k > 0 && AliceStart[i - 1] == AliceEnd[k - 1]) add(f[i][j][k], f[i - 1][j][k - 1]);
                        if (i > 0 && l > 0 && AliceStart[i - 1] == BobEnd[l - 1]) add(f[i][j][k], f[i - 1][j][k]);
                        if (j > 0 && k > 0 && BobStart[j - 1] == AliceEnd[k - 1]) add(f[i][j][k], f[i][j - 1][k - 1]);
                        if (j > 0 && l > 0 && BobStart[j - 1] == BobEnd[l - 1]) add(f[i][j][k], f[i][j - 1][k]);
                    }
                }
            }

            return f[AliceStart.size()][BobStart.size()][AliceEnd.size()];
        }
};

