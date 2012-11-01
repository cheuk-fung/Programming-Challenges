#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-8;
inline bool gr(double x, double y) { return x - eps > y; }
inline bool lseq(double x, double y) { return x - eps <= y; }

template<class T> inline T SQR(T x) { return x * x; }
template<class T> inline int SIZE(const T &x) { return x.size(); }

long long x[555], y[555], p[555];
double r[555];
vector<double> radius(555);
vector<int> s;

void RELAX(int i, int j)
{
    int t = s[j];
    radius[i] = min(radius[i], (double)SQR(x[i] - x[t]) / (4.0 * radius[t]));
}

double solve(int n, int mx)
{
    double sum = 0;
    for (int i = 0; i < n; i++) {
        radius[i] = p[i];
        for (int j = 0; j < min(SIZE(s), mx); j++) {
            RELAX(i, SIZE(s) - j - 1);
        }
        while (!s.empty() && lseq(radius[s.back()], radius[i])) s.pop_back();
        s.push_back(i);
        sum += radius[i];
    }
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    x[1] = 37600;
    r[1] = 1;
    p[1] = 1;
    for (int i = 2; i <= 300; i++) {
        for (int j = x[i - 1] + 1; ; j++) {
            if (gr(ceil(r[i] = (double)SQR(j - x[i - 1]) / (4.0 * r[i - 1])), p[i - 1])) {
                x[i] = j;
                p[i] = ceil(r[i]);
                break;
            }
        }
    }
    x[0] = 0;
    p[0] = 1000000;
    p[301] = 1000000;
    for (int i = 2; i <= 300; i++) y[i] = x[i] - x[i - 1];
    reverse(y + 2, y + 301);
    for (int i = 2; i <= 300; i++) x[i] = x[i - 1] + y[i];
    reverse(p + 1, p + 301);
    x[301] = 200000;
    /*
    double chk = solve(301, 300);
    printf("%d\n", SIZE(s));
    s.clear();
    chk = solve(302, 300);
    s.clear();
    double sum = solve(302, 500);
    printf("%.10f %.10f\n", sum, chk);
    */
    cout << 302 << endl;
    for (int i = 0; i < 302; i++) {
        cout << x[i] << ' ' << p[i] << endl;
    }

    return 0;
}

