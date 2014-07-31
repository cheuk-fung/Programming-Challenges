#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

class Ear {
    private:
        vector<int> parse(vector<string> vs)
        {
            string str = "";
            for (int i = 0; i < SIZE(vs); i++) str += vs[i];
            istringstream is(str);
            vector<int> res;
            for (int x; is >> x; res.push_back(x)) ;
            return res;
        }

        int cross(int x1, int y1, int x2, int y2) { return x1 * y2 - y1 * x2; }

    public:
        long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
        {
            vector<int> rX = parse(redX);
            vector<int> bX = parse(blueX);
            vector<int> bY = parse(blueY);
            assert(SIZE(bX) == SIZE(bY));

            int n = SIZE(rX), m = SIZE(bX);
            if (n < 4 || m < 2) return 0;

            sort(rX.begin(), rX.end());

            long long res = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (bY[i] <= bY[j]) continue;
                    if (!(rX[0] < bX[i] && rX[1] < bX[j] && rX[n - 1] > bX[i] && rX[n - 2] > bX[j])) continue;

                    int l = 0, lCnt = lower_bound(rX.begin(), rX.end(), bX[j]) - rX.begin();
                    while (l < n && rX[l] < bX[i] && rX[l] < bX[j] && cross(bX[i] - rX[l], bY[i], bX[j] - rX[l], bY[j]) < 0) l++;
                    int r = n - 1, rCnt = rX.end() - upper_bound(rX.begin(), rX.end(), bX[j]);
                    while (r >= 0 && rX[r] > bX[i] && rX[r] > bX[j] && cross(bX[i] - rX[r], bY[i], bX[j] - rX[r], bY[j]) > 0) r--;
                    r = n - 1 - r;
                    long long lRes = (long long)(lCnt - l + lCnt - 1) * l / 2;
                    long long rRes = (long long)(rCnt - r + rCnt - 1) * r / 2;
                    res += lRes * rRes;
                }
            }

            return res;
        }
};
