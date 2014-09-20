#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class Stamp {
    private:
        int f[55][255];

        int dp(int x, int l, string desiredColor)
        {
            if (x < 0) return 0;
            int color = desiredColor[x];

            if (f[x][color] != -1) return f[x][color];
            if (x + 1 < l) return f[x][color] = INF;

            int tmpColor = '*';
            for (int i = x; i > x - l; i--) {
                if (desiredColor[i] != '*' && color != '*' && desiredColor[i] != color) {
                    return f[x][color] = INF;
                }
                if (desiredColor[i] != '*' && color == '*') {
                    if (tmpColor != '*' && desiredColor[i] != tmpColor) {
                        return f[x][color] = INF;
                    }
                    tmpColor = desiredColor[i];
                }
            }

            f[x][color] = INF;
            if (color != '*') tmpColor = color;
            string now = desiredColor;
            for (int i = x; i > x - l; i--) now[i] = tmpColor;
            for (int i = x - 1; i >= x - l; i--) {
                f[x][color] = min(f[x][color], dp(i, l, now));
            }

            return f[x][color] += 1;
        }

    public:
        int getMinimumCost(string desiredColor, int stampCost, int pushCost)
        {
            int res = INF;
            int n = SIZE(desiredColor);
            for (int l = 1; l <= n; l++) {
                memset(f, 0xff, sizeof f);
                int ret = dp(n - 1, l, desiredColor);
                if (ret < INF) {
                    res = min(res, stampCost * l + pushCost * ret);
                }
            }
            return res;
        }
};
