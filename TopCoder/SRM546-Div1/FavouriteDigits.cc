#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

class FavouriteDigits {
    private:
        unsigned long long ten[22];

        pii count(long long n, int p, int digit1, int digit2)
        {
            n /= ten[p];

            int cnt1 = 0, cnt2 = 0;
            while (n) {
                if (n % 10 == digit1) cnt1++;
                else if (n % 10 == digit2) cnt2++;
                n /= 10;
            }
            return pii(cnt1, cnt2);
        }

    public:
        long long findNext(long long N, int digit1, int count1, int digit2, int count2)
        {
            ten[0] = 1;
            for (int i = 1; i < 21; i++) ten[i] = ten[i - 1] * 10;

            pii cnt = count(N, 0, digit1, digit2);
            if (cnt.first >= count1 && cnt.second >= count2) return N;

            if (digit1 > digit2) {
                swap(digit1, digit2);
                swap(count1, count2);
            }
            for (int i = 0; i < 20; i++) {
                unsigned long long t = N / ten[i] * ten[i];
                unsigned long long t2 = N / ten[i + 1] * ten[i + 1];
                t += ten[i];
                while (t / ten[i + 1] * ten[i + 1] == t2) {
                    cnt = count(t, i, digit1, digit2);
                    int a = max(0, count1 - cnt.first);
                    int b = max(0, count2 - cnt.second);
                    if (a + b <= i) {
                        unsigned long long x = 0;
                        for (int k = cnt.first; k < count1; k++) x = x * 10 + digit1;
                        for (int k = cnt.second; k < count2; k++) x = x * 10 + digit2;
                        return t + x;
                    }
                    t += ten[i];
                }
            }
        }
};

