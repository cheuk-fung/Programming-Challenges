#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

queue<int> que;
int lev[1 << 20];

inline void expand(int v, int l)
{
    if (lev[v] == -1) {
        lev[v] = l;
        que.push(v);
    }
}

int main()
{
    int n, m;
    string str;
    while (cin >> n >> str >> m) {
        int clipper = 0;
        int rev_clipper = 0;
        for (int i = 0; i < n; i++) {
            clipper = (clipper << 1) + (str[i] == '*');
            rev_clipper = (rev_clipper << 1) + (str[n - i - 1] == '*');
        }

        if (clipper == 0) {
            cout << -1 << endl;
            continue;
        }

        while (!que.empty()) que.pop();
        memset(lev, 0xff, sizeof lev);

        que.push(0);
        lev[0] = 0;
        int target = (1 << m) - 1;
        while (!que.empty()) {
            int u = que.front();
            if (u == target) {
                cout << lev[u] << endl;
                break;
            }
            que.pop();

            for (int i = 0; i < m + n; i++) {
                long long x = clipper, y = rev_clipper;
                if (i < n) {
                    x >>= n - i;
                    y >>= n - i;
                } else {
                    x <<= (i - n);
                    x &= target;
                    y <<= (i - n);
                    y &= target;
                }
                expand(u | x, lev[u] + 1);
                expand(u | y, lev[u] + 1);
            }
        }
    }

    return 0;
}
