#include <cstring>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int f[27][27][27][27][27];
class EllysFiveFriends {
    private:
        int idx[5][10010];

        void get_idx(int p, int n, int id)
        {
            idx[p][n] = id;
            if (!n) return ;
            if (n % 2) get_idx(p, n - 1, id + 1);
            else get_idx(p, n / 2, id + 1);
        }

        int dp(const int *numbers)
        {
            int id[5];
            for (int i = 0; i < 5; i++) id[i] = idx[i][numbers[i]];
            int *res = &f[id[0]][id[1]][id[2]][id[3]][id[4]];
            if (*res != -1) return *res;

            *res = 0;
            for (int i = 0; i < 5; i++) {
                int j = (i + 1) % 5;
                if (!numbers[i] || !numbers[j]) continue;
                int t[5];
                memcpy(t, numbers, sizeof(int) * 5);
                if (t[i] % 2 && t[j] % 2) {
                    t[i]--; t[j]--;
                    *res = (*res + dp(t)) % MOD;
                    t[i]++; t[j]++;
                }
                t[i] /= 2; t[j] /= 2;
                *res = (*res + dp(t)) % MOD;
            }

            return *res;
        }

    public:
        int getZero(vector <int> numbers)
        {
            int a[5];
            for (int i = 0; i < 5; i++) a[i] = numbers[i];
            for (int i = 0; i < 5; i++) get_idx(i, a[i], 0);
            memset(f, 0xff, sizeof(f));
            f[idx[0][0]][idx[1][0]][idx[2][0]][idx[3][0]][idx[4][0]] = 1;
            return dp(a);
        }
};
