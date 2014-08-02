/*
 *  SRC: HDOJ 4082
 * PROB: Hou Yi's secret
 * ALGO: NULL
 * DATE: Sep 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ng
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

pair<int, int> pnt[20];

struct Triangle {
    int e[3];
} tri[1000];

inline int SQR(int x) { return  x * x; }
inline int dist(int a, int b) { return SQR(pnt[a].first - pnt[b].first) + SQR(pnt[a].second - pnt[b].second); }
inline int cross(int a, int b, int c) { return (pnt[a].first - pnt[c].first) * (pnt[b].second - pnt[c].second) - (pnt[a].second - pnt[c].second) * (pnt[b].first - pnt[c].first); }

bool can(int i, int j, int k)
{
    return cross(i, j, k) != 0 && sqrt(dist(i, j)) + sqrt(dist(j, k)) > sqrt(dist(k, i)) && sqrt(dist(i, j)) - sqrt(dist(j, k)) < sqrt(dist(k, i));
}

int main()
{
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &pnt[i].first, &pnt[i].second);
        }
        sort(pnt, pnt + n);
        n = unique(pnt, pnt + n) - pnt;

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (can(i, j, k)) {
                        tri[cnt] = (Triangle){{dist(i, j), dist(j, k), dist(k, i)}};
                        sort(tri[cnt].e, tri[cnt].e + 3);
                        cnt++;
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < cnt; i++) {
            int now = 1;
            for (int j = 0; j < cnt; j++) {
                if (i == j) continue;
                if (tri[i].e[0] * tri[j].e[1] == tri[i].e[1] * tri[j].e[0] && tri[i].e[0] * tri[j].e[2] == tri[i].e[2] * tri[j].e[0]) {
                    now++;
                }
            }
            ans = max(ans, now);
        }

        printf("%d\n", ans);
    }

    return 0;
}

