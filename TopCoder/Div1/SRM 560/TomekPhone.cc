#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class TomekPhone {
    public:
        int minKeystrokes(vector <int> occurences, vector <int> keySizes) {
            sort(occurences.begin(), occurences.end());
            sort(keySizes.begin(), keySizes.end(), greater<int>());
            int sum = 0;
            for (int i = 0; i < (int)keySizes.size(); i++) sum += keySizes[i];
            if (sum < (int)occurences.size()) return -1;

            int ans = 0;
            int round = 1;
            while (!occurences.empty()) {
                for (int i = 0; i < (int)keySizes.size(); i++) {
                    if (keySizes[i] == 0) continue;
                    keySizes[i]--;
                    ans += round * occurences.back();
                    occurences.pop_back();
                    if (occurences.empty()) break;
                }
                round++;
            }
            return ans;
        }
};
