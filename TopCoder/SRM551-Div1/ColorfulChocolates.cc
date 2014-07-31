#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;
template<class T> inline int SIZE(const T &x) { return x.size(); }

class ColorfulChocolates {
    private:

    public:
        int maximumSpread(string chocolates, int maxSwaps)
        {
            int ans = 0;

            for (int i = 0; i < SIZE(chocolates); i++) {
                char c = chocolates[i];
                int times = 0;
                int cnt = 1;
                int lcnt = 0, rcnt = 0;
                for (int j = i - 1, k = i + 1; ; ) {
                    while (j >= 0 && chocolates[j] != c) j--;
                    while (k < SIZE(chocolates) && chocolates[k] != c) k++;
                    int ltimes = j >= 0 ? i - j - lcnt - 1 : INF;
                    int rtimes = k < SIZE(chocolates) ? k - i - rcnt - 1 : INF;
                    times += min(ltimes, rtimes);
                    if (times <= maxSwaps) {
                        cnt++;
                        if (ltimes < rtimes) {
                            lcnt++;
                            j--;
                        } else {
                            rcnt++;
                            k++;
                        }
                    } else {
                        break;
                    }
                }

                ans = max(ans, cnt);
            }

            return ans;
        }
};
