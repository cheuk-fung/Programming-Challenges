#include <algorithm>

using namespace std;

class FoxPaintingBalls {
    private:

    public:
        long long theMax(long long R, long long G, long long B, int N)
        {
            if (N == 1) {
                return R + G + B;
            }

            long long tot = (N + 1ll) * N / 2ll;
            long long single = tot / 3;
            long long color[3] = {R, G, B};
            sort(color, color + 3);

            if (tot % 3 != 1) return color[0] / single;

            long long cnt = color[2] - color[1];
            if (color[2] / (single + 1) <= cnt || color[0] / single <= cnt) return min(color[2] / (single + 1), color[0] / single);
            color[2] -= cnt * (single + 1);
            color[1] -= cnt * single;
            color[0] -= cnt * single;

            long long res = cnt;
            cnt = color[1] - color[0];
            if (color[1] / (single * 2 + 1) <= cnt || color[0] / (single * 2) <= cnt) {
                cnt = min(color[1] / (single * 2 + 1), color[0] / (single * 2));
                res += cnt * 2;
                color[2] -= cnt * (single * 2 + 1);
                color[1] -= cnt * (single * 2 + 1);
                color[0] -= cnt * single * 2;
                if (color[2] < single + 1 || color[0] < single) return res;
                return res + 1;
            }
            color[2] -= cnt * (single * 2 + 1);
            color[1] -= cnt * (single * 2 + 1);
            color[0] -= cnt * single * 2;

            res += cnt * 2;
            cnt = color[0] / (single * 3 + 1);
            color[2] -= cnt * (single * 3 + 1);
            color[1] -= cnt * (single * 3 + 1);
            color[0] -= cnt * (single * 3 + 1);
            res += cnt * 3;
            if (color[2] < single + 1) return res;
            color[2] -= single + 1;
            color[1] -= single;
            color[0] -= single;
            res++;
            if (color[1] < single + 1) return res;
            return res + 1;
        }
};
