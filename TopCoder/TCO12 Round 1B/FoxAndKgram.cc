#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<class T> inline T sqr(T x) { return x * x; }

class FoxAndKgram {
    private:
        bool check(int k, vector<int> len)
        {
            int cnt = 0;
            bool used[len.size()];
            memset(used, 0, sizeof(used));
            for (int i = 0; i < len.size(); i++) {
                if (len[i] > k) continue;
                if (!used[i]) {
                    if (len[i] == k) {
                        cnt++;
                        used[i] = 1;
                    } else {
                        for (int j = 0; j < len.size(); j++) {
                            if (i != j && !used[j] && len[i] + len[j] == k - 1) {
                                cnt++;
                                used[i] = 1;
                                used[j] = 1;
                                break;
                            }
                        }
                    }
                }
            }

            return cnt >= k;
        }

    public:
        int maxK(vector<int> len)
        {
            sort(len.begin(), len.end(), greater<int>());
            int k = len[0] * 2 + 1;
            while (true) {
                if (check(k, len)) {
                    return k;
                }
                k--;
            }
        }
};
