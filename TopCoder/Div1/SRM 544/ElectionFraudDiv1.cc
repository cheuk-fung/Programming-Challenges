#include <algorithm>
#include <vector>

using namespace std;

class ElectionFraudDiv1 {
    private:
        bool check(long long sum, vector<int> &p)
        {
            long long low = 0, high = 0;
            for (int i = 0; i < p.size(); i++) {
                low += (sum * max(0, p[i] * 2 - 1) + 199) / 200;
                high += (sum * min(200, p[i] * 2 + 1) + 199) / 200 - 1;
            }
            if (low > sum || high < sum) return false;

            return true;
        }

    public:
        int MinimumVoters(vector <int> percentages)
        {
            if (count(percentages.begin(), percentages.end(), 0) == percentages.size() - 1 && count(percentages.begin(), percentages.end(), 100) == 1) return 1;

            double low = 0, high = 0;
            for (int i = 0; i < percentages.size(); i++) {
                low += max(0, percentages[i] * 2 - 1);
                high += min(200, percentages[i] * 2 + 1);
            }
            if (low > 200 || high <= 200) return -1;

            int ans = 1;
            while (!check(ans, percentages)) ans++;
            return ans;
        }
};

