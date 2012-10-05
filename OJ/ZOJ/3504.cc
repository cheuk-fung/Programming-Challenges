/*
 *  SRC: ZOJ 3504
 * PROB: P-norm
 * ALGO: NULL
 * DATE: Oct 05, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;

typedef pair<double, double> pdd;

char *line;

inline double SQR(double x) { return x * x; }

vector<pdd> get_vector(char *line)
{
    vector<pdd> r;
    while (*line != '\n') {
        double x, y;
        sscanf(line, " (%lf,%lf)", &x, &y);
        r.push_back(pdd(x, y));
        while (*line != ')') line++;
        line++;
    }
    return r;
}

int main()
{
    size_t size = 0;
    while (~getline(&line, &size, stdin)) {
        vector<pdd> v, w;
        v = get_vector(line);
        getline(&line, &size, stdin);
        w = get_vector(line);

        double p;
        scanf("%lf\n", &p);

        double ans = 0;
        for (int i = 0; i < (int)v.size(); i++) {
            ans += pow(SQR(v[i].first - w[i].first) + SQR(v[i].second - w[i].second), p / 2.0);
        }
        ans = pow(ans, 1.0 / p);

        printf("%.10f\n", ans);

    }

    return 0;
}

