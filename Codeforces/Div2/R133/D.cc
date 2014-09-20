#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

template<class T> inline int SIZE(const T &x) { return x.size(); }

vector<int> dis[1010];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int d;
            scanf("%d", &d);
            dis[i].push_back(d);
        }
        sort(dis[i].begin(), dis[i].end());
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int plast = 0, nlast = 0;
        int prev = (i - 1 + n) % n, next = (i + 1) % n;
        for (int j = 1; j < SIZE(dis[i]); j++) {
            int pl = lower_bound(dis[prev].begin() + plast, dis[prev].end(), dis[i][j - 1]) - dis[prev].begin();
            int pr = upper_bound(dis[prev].begin() + plast, dis[prev].end(), dis[i][j]) - dis[prev].begin();
            plast = pr;

            int nl = lower_bound(dis[next].begin() + nlast, dis[next].end(), dis[i][j - 1]) - dis[next].begin();
            int nr = upper_bound(dis[next].begin() + nlast, dis[next].end(), dis[i][j]) - dis[next].begin();
            nlast = nr;

            if (pr - pl != nr - nl) cnt++;
        }
    }

    printf("%d\n", cnt);


    return 0;
}

