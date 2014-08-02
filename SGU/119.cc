#include <cstdio>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

int main(int argc, char *argv[])
{
    int n, A0, B0;
    scanf("%d%d%d", &n, &A0, &B0);

    set<pii> ans;
    for (int k = 0; k < n; k++) {
        ans.insert(pii(A0 * k % n, B0 * k % n));
    }
    printf("%d\n", ans.size());
    for (set<pii>::iterator it = ans.begin(); it != ans.end(); it++) {
        printf("%d %d\n", it->first, it->second);
    }

    return 0;
}
