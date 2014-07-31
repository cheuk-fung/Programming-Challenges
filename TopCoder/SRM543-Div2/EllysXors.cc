#include <cstdio>

class EllysXors {
    private:
        long long calc(long long x)
        {
            switch (x % 4) {
                case 0: return x;
                case 1: return x ^ (x - 1);
                case 2: return x ^ (x - 1) ^ (x - 2);
                case 3: return 0;
            }
        }

    public:
        long long getXor(long long L, long long R)
        {
            return calc(L - 1) ^ calc(R);
        }
};
