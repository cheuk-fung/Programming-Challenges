#include <cstdio>
#include <algorithm>

using namespace std;

class EllysXors {
    private:
        long long calc(long long p)
        {
            long long res = (p % 4 == 1 || p % 4 == 2);
            long long mi = 2;
            while (mi <= p) {
                res += mi * (min((p - mi + 1) % (mi << 1), mi) & 1);
                mi <<= 1;
            }
            return res;
        }

    public:
        long long getXor(long long L, long long R)
        {
            return calc(L - 1) ^ calc(R);
        }
};
