#include <cstring>
#include <string>

using namespace std;

class MagicStonesStore {
    private: 
        int prm[5000];
        bool is_prm[5000];

        int get_prime(int n, int* p, bool* b)
        {
            int cnt = 0;
            memset(b, true, sizeof(bool) * n);
            b[0] = b[1] = false;
            for (int i = 2; i < n; i++) {
                if (b[i]) p[cnt++] = i;
                for (int j = 0; j < cnt && i * p[j] < n; j++) {
                    b[i * p[j]] = false;
                    if (i % p[j] == 0) break;
                }
            }

            return cnt;
        }

    public:
        string ableToDivide(int n)
        {
            int prm_cnt = get_prime(3000, prm, is_prm);

            for (int i = 0; i < prm_cnt && prm[i] < 2 * n; i++)
                if (is_prm[2 * n - i]) return "YES";
            return "NO";
        }
};
