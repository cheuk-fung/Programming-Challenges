#include <cstring>
#include <string>

using namespace std;

class StrIIRec {
    private:
        int n, minInv;
        string minStr;
        string r;
        int tot;
        bool vis[256];

        bool gen(int x, bool tail)
        {
            if (x == n) return true;

            int c;
            int low = tail || x >= minStr.length() ? 'a' : minStr[x];
            char cc = 0;
            for (c = low; c < 'a' + n; c++) {
                if (vis[c]) continue;

                int cnt = 0;
                vis[c] = true;
                for (int k = 'a'; k < c; k++) {
                    if (!vis[k]) cnt++;
                }

                for (int j = 'a'; j <= 'a' + n - 1; j++) {
                    if (vis[j]) continue;
                    for (int k = 'a'; k < j; k++) {
                        if (!vis[k]) cnt++;
                    }
                }
                vis[c] = false;
                if (tot + cnt >= minInv) break;
            }
            r += (char)c;
            for (int k = 'a'; k < c; k++) {
                if (!vis[k]) tot++;
            }
            vis[c] = true;

            if (x + 1 >= minStr.length() || tail || c != minStr[x]) {
                return gen(x + 1, true);
            }

            if (gen(x + 1, false)) return true;

            for (int k = 'a'; k < c; k++) {
                if (!vis[k]) tot--;
            }
            vis[c] = false;
            r[r.length() - 1] = (char)(c + 1);
            vis[c + 1] = true;
            return gen(x + 1, true);
        }

    public:
        string recovstr(int _n, int _minInv, string _minStr)
        {
            n = _n;
            minInv = _minInv;
            minStr = _minStr;

            if (minInv > n * (n - 1) / 2) return "";

            r = "";
            tot = 0;
            memset(vis, 0, sizeof(vis));
            gen(0, false);

            return r;
        }
};

