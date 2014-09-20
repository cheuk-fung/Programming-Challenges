#include <algorithm>

using namespace std;

class TheBrickTowerEasyDivOne {
    private:

    public:
        int find(int redCount, int redHeight, int blueCount, int blueHeight)
        {
            int res = min(redCount, blueCount) << 1;
            if (redHeight != blueHeight) {
                res += min(redCount, blueCount);
            }
            if (redCount != blueCount) {
                res++;
            }
            return res;
        }
};
