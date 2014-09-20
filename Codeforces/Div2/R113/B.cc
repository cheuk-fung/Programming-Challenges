#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<long long, long long> pii;

int n, m;
vector<pii> A, B;

pii operator-(pii u, pii v)
{
    return pii(u.first - v.first, u.second - v.second);
}

long long operator^(pii u, pii v)
{
    return u.first * v.second - u.second * v.first;
}

bool in_polygon_A(pii p)
{
    if (((A[0] - p) ^ (A[1] - p)) >= 0) {
        return false;
    }

    int l = 1, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (((A[0] - p) ^ (A[mid] - p)) <= 0) l = mid;
        else r = mid - 1;
    }

    return ((A[l] - p) ^ (A[(l + 1) % n] - p)) < 0;
}

bool check()
{
    for (int i = 0; i < m; i++) {
        if (!in_polygon_A(B[i])) {
            return false;
        }
    }

    return true;
}

int main()
{
    while (cin >> n) {
        A.clear();
        B.clear();

        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            A.push_back(pii(x, y));
        }

        cin >> m;
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            B.push_back(pii(x, y));
        }

        puts(check() ? "YES" : "NO");
    }

    return 0;
}

