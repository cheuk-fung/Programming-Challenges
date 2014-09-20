#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;
template<class T> inline int SIZE(const T &x) { return x.size(); }

class CuttingBitString {
    private:
        bool check(string S)
        {
            long long x = 0;
            for (int i = 0; i < SIZE(S); i++) {
                x <<= 1;
                if (S[i] == '1') x++;
            }
            if (!x) return false;
            while (x % 5 == 0) x /= 5;
            return x == 1;
        }

        int cut(string S)
        {
            if (S[0] == '0') return -1;
            if (check(S)) return 1;

            int res = INF;
            for (int i = 1; i < SIZE(S); i++) {
                if (check(S.substr(0, i))) {
                    int r = cut(S.substr(i));
                    if (r == -1) continue;
                    res = min(res, r + 1);
                }
            }
            return res == INF ? -1 : res;
        }

    public:
        int getmin(string S)
        {
            return cut(S);
        }
};
