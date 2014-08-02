#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
const int MAXN = 16000;

pii outpost[MAXN];

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &outpost[i].first, &outpost[i].second);
    }
    sort(outpost, outpost + n);

    int cnt = 0;
    pii now = outpost[0];
    for (int i = 1; i < n; i++) {
        if (outpost[i].second < now.second) cnt++;
        else now = outpost[i];
    }
    printf("%d\n", cnt);

    return 0;
}
