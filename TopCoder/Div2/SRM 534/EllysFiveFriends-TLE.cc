#include <vector>
#include <map>

using namespace std;

const int MOD = 1000000007;

map<vector<int>, int> f;

class EllysFiveFriends {
    private:
        int dp(vector<int> &numbers)
        {
            if (f.count(numbers)) return f[numbers];

            long long res = 0;
            for (int i = 0; i < 5; i++) {
                int j = (i + 1) % 5;
                if (!numbers[i] || !numbers[j]) continue;
                vector<int> t = numbers;
                if (t[i] % 2 && t[j] % 2) {
                    t[i]--; t[j]--;
                    res = (res + dp(t)) % MOD;
                    t[i]++; t[j]++;
                }
                t[i] /= 2; t[j] /= 2;
                res = (res + dp(t)) % MOD;
            }

            return f[numbers] = res;
        }

    public:
        int getZero(vector <int> numbers)
        {
            vector<int> init;
            for (int i = 0; i < 5; i++) init.push_back(0);
            f[init] = 1;
            return dp(numbers);
        }
};
