#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> pii;

int cntm[4096];
vector<int> cost[4096];
vector<int> money;
vector<pii> mass;

int main(int argc, char *argv[])
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        int m, c;
        scanf("%d%d", &m, &c);
        cntm[m]++;
        cost[m].push_back(c);
    }
    for (int i = 0; i < 4096; i++) {
        if (cntm[i]) {
            mass.push_back(pii(cntm[i], i));
        }
    }
    if ((int)mass.size() < k) {
        puts("0 0");
        return 0;
    }

    sort(mass.begin(), mass.end());
    reverse(mass.begin(), mass.end());

    int cnt = mass[k - 1].first;
    while (mass.back().first != cnt) mass.pop_back();
    for (int i = 0; i < (int)mass.size(); i++) {
        int now = mass[i].second;
        sort(cost[now].begin(), cost[now].end(), greater<int>());
        int sum = 0;
        for (int j = 0; j < cnt; j++) sum += cost[now][j];
        money.push_back(sum);
    }
    sort(money.begin(), money.end(), greater<int>());
    int sum = 0;
    for (int i = 0; i < k; i++) sum += money[i];

    printf("%d %d\n", cnt, sum);

    return 0;
}
