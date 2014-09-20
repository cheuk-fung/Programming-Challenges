#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f;

class KingdomAndTrees {
    private:
        bool check(int x, const vector<int> &heights)
        {
            int pre = 0;
            for (int i = 0; i < heights.size(); i++) {
                if (heights[i] <= pre) {
                    if (heights[i] + x <= pre) return false;
                    pre++;
                } else {
                    pre = max(pre + 1, heights[i] - x);
                }
            }
            return true;
        }

    public:
        int minLevel(vector <int> heights)
        {
            int l = 0, r = INF;
            while (l < r) {
                int mid = (l + r - 1) / 2;
                if (check(mid, heights)) r = mid;
                else l = mid + 1;
            }
            return l;
        }
};

