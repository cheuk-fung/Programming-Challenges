#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int>::const_iterator vci;
const int INF = 0x3f3f3f3f;

class KingdomAndDice {
    private:
        bool f[5000][100];

        void zero_one_pack(int value, int amount, int max_value, int max_amount)
        {
            for (int i = max_value; i >= value; i--)
                for (int j = max_amount; j >= amount; j--)
                    if (f[i - value][j - amount]) f[i][j] = true;
        }

        void multiple_pack(int value, int amount, int max_value, int max_amount)
        {
            if (amount <= 0) return;

            amount = min(amount, max_amount);
            for (int k = 1; k < amount; amount -= k, k <<= 1)
                zero_one_pack(k * value, k, max_value, max_amount);

            zero_one_pack(value * amount, amount, max_value, max_amount);
        }

    public:
        double newFairness(vector <int> firstDie, vector <int> secondDie, int X)
        {
            int win = 0;
            for (vci i = firstDie.begin(); i != firstDie.end(); i++)
                for (vci j = secondDie.begin(); j != secondDie.end(); j++)
                    if (*i > *j) win++;

            int zeros = count(firstDie.begin(), firstDie.end(), 0);

            sort(secondDie.begin(), secondDie.end());
            secondDie.push_back(X + 1);

            int max_value = firstDie.size() * firstDie.size();
            int max_amount = zeros;
            memset(f, 0, sizeof(f));
            f[0][0] = true;
            for (int i = 1; i <= (int)secondDie.size(); i++) {
                int cnt = secondDie[i] - secondDie[i - 1] - 1;
                for (int j = 0; j < (int)firstDie.size(); j++)
                    if (secondDie[i - 1] < firstDie[j] && firstDie[j] < secondDie[i]) cnt--;
                multiple_pack(i, cnt, max_value, max_amount);
            }

            int gap = INF;
            int ans;
            for (int i = 0; i <= max_value; i++)
                for (int j = 0; j <= max_amount; j++)
                    if (f[i][j])
                        if (abs(max_value - (win + i) * 2) < gap) {
                            gap = abs(max_value - (win + i) * 2);
                            ans = win + i;
                            break;
                        }

            return (double)ans / max_value;
        }
};

