#include <cstdio>
#include <algorithm>

using std::sort;

struct Boy {
    int s, id;
    bool operator <(const Boy &other) const { return s > other.s; }
} p[100010];

int n;
int x[100010], y[100010];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].s);
        p[i].id = i + 1;
    }
    sort(p, p + n);
    int x_tot = 0, y_tot = 0;
    int x_cnt = 0, y_cnt = 0;
    for (int i = 0; i + 1 < n; i += 2) {
        if (abs(x_tot + p[i].s - (y_tot + p[i + 1].s)) < \
            abs(x_tot + p[i + 1].s - (y_tot + p[i].s))) {
            x_tot += p[i].s;
            x[x_cnt++] = p[i].id;
            y_tot += p[i + 1].s;
            y[y_cnt++] = p[i + 1].id;
        }
        else {
            x_tot += p[i + 1].s;
            x[x_cnt++] = p[i + 1].id;
            y_tot += p[i].s;
            y[y_cnt++] = p[i].id;
        }
    }
    if (n % 2) {
        if (abs(x_tot + p[n - 1].s - y_tot) < abs(x_tot - (y_tot + p[n - 1].s)))
            x[x_cnt++] = p[n - 1].id;
        else y[y_cnt++] = p[n - 1].id;
    }

    printf("%d\n", x_cnt);
    for (int i = 0; i < x_cnt; i++)
        printf("%d%c", x[i], i == x_cnt - 1 ? '\n' : ' ');
    printf("%d\n", y_cnt);
    for (int i = 0; i < y_cnt; i++)
        printf("%d%c", y[i], i == y_cnt - 1 ? '\n' : ' ');

    return 0;
}

