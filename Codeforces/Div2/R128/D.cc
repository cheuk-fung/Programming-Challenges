#include <iostream>
#include <cstdio>

using namespace std;

const double eps = 1e-8;

inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

int main()
{
    int a, b, m;
    while (cin >> a >> b >> m) {
        int vx, vy, vz;
        cin >> vx >> vy >> vz;
        double time = (double)m / vy * -1.0;
        double x = a / 2.0 + vx * time;
        double z = vz * time;

        while (ls(x, 0) || gr(x, a)) {
            if (ls(x, 0)) x *= -1;
            else x = a * 2 - x;
        }
        while (ls(z, 0) || gr(z, b)) {
            if (ls(z, 0)) z *= -1;
            else z = b * 2 - z;
        }

        printf("%.10lf %.10lf\n", x, z);
    }

    return 0;
}

