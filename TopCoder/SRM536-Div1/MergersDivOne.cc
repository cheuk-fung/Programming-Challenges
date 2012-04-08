#include <algorithm>
#include <vector>

using namespace std;

template<class T> inline T sqr(T x) { return x * x; }

class MergersDivOne {
    private:

    public:
        double findMaximum(vector <int> revenues)
        {
            sort(revenues.begin(), revenues.end());
            double res = revenues[0];
            for (int i = 1; i < revenues.size(); i++)
                res = (res + revenues[i]) / 2.0;
            return res;
        }
};
