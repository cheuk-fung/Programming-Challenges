#include <string>

using namespace std;

class TheNumberGameDivOne {
    private:

    public:
        string find(long long n)
        {
            if (n & 1) return "Brus";
            int cnt = -1;
            for (long long x = n; x; x >>= 1) cnt++;
            if (n == (1ll << cnt) && (cnt & 1)) return "Brus";
            return "John";
        }
};
