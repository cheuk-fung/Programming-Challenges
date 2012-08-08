#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 15000;

struct City {
    int x, p;
    bool operator<(const City &o) const { return x < o.x; }
} c[MAXN];

long long lp[MAXN], rp[MAXN];

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &c[i].x, &c[i].p);
    }
    sort(c, c + n);

    lp[0] = c[0].p;
    for (int i = 1; i < n; i++) {
        lp[i] = lp[i - 1] + c[i].p;
    }
    rp[n - 1] = c[n - 1].p;
    for (int i = n - 2; i >= 0; i--) {
        rp[i] = rp[i + 1] + c[i].p;
    }

    int ans = c[0].x;
    long long min_displeasure = 0;
    long long displeasure = 0;
    for (int i = 1; i < n; i++) {
        displeasure += (long long)c[i].p * (c[i].x - c[0].x);
    }

    min_displeasure = displeasure;
    for (int i = 1; i < n; i++) {
        displeasure += (lp[i - 1] - rp[i]) * (c[i].x - c[i - 1].x);
        if (displeasure < min_displeasure) {
            min_displeasure = displeasure;
            ans = c[i].x;
        }
    }

    printf("%.5f\n", (double)ans);

    return 0;
}
