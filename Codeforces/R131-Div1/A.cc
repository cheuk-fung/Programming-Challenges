#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 210;

template<class T> inline int SIZE(const T &x) { return x.size(); }

int n;
int c[MAXN], deg[MAXN], work[MAXN];
vector<int> e[MAXN];

int run(int st)
{
    memcpy(work, deg, sizeof deg);
    int res = 0;
    while (true) {
        int flag = true;
        for (int j = 1; j <= n; j++) {
            if (work[j] >= 0) {
                flag = false;
                break;
            }
        }
        if (flag) break;

        flag = true;
        for (int j = 1; j <= n; j++) {
            if (c[j] == st && work[j] == 0) {
                flag = false;
                for (int k = 0; k < SIZE(e[j]); k++) {
                    work[e[j][k]]--;
                }
                work[j] = -1;
            }
        }
        if (flag) {
            st = (st + 1) % 3;
            res++;
        }
    }
    return res;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        c[i]--;
    }
    for (int i = 1; i <= n; i++) {
        cin >> deg[i];
        for (int j = 0; j < deg[i]; j++) {
            int a;
            cin >> a;
            e[a].push_back(i);
        }
    }

    int ans = min(run(0), min(run(1), run(2))) + n;
    cout << ans << endl;

    return 0;
}

