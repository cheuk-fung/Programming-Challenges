#include <cstdio>
#include <cstring>

const int MOD = 1000000007;

class NoRepeatPlaylist {
    private:
        int m, p;
        long long f[101][101][101];

        long long count(int pos, int x, int y)
        {
            if (pos == p) return y == 0;
            if (f[pos][x][y] != -1) return f[pos][x][y];

            long long ans = 0;
            if (x > m) ans += count(pos + 1, x, y) * (x - m);
            if (y > 0) ans += count(pos + 1, x + 1, y - 1) * y;

            return f[pos][x][y] = (ans % MOD);
        }

    public:
        int numPlaylists(int N, int M, int P)
        {
            m = M;
            p = P;
            memset(f, 0xff, sizeof(f));
            return count(0, 0, N);
        }
};
