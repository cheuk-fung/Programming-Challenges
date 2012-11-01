#include <algorithm>

using namespace std;

class HyperKnight {
    private:
        long long run(long long a, long long b, long long numRows, long long numColumns, int k)
        {
            if (a < b) {
                swap(a, b);
                swap(numRows, numColumns);
            }
            if (k == 8) return (numRows - 2 * a) * (numColumns - 2 * a);
            if (k == 6) return (a - b) * (numRows - 2 * a) * 2 + (a - b) * (numColumns - 2 * a) * 2;
            if (k == 4) return (a - b) * (a - b) * 4 + b * (numRows - 2 * a) * 2 + b * (numColumns - 2 * a) * 2;
            if (k == 3) return b * (a - b) * 8;
            if (k == 2) return b * b * 4;
            return 0;
        }

    public:
        long long countCells(int a, int b, int numRows, int numColumns, int k)
        {
            return run(a, b, numRows, numColumns, k);
        }
};
