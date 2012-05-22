#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef pair<double, double> pdd;

const double DINF = 1.0/0.0f;
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }
inline bool greq(double x, double y) { return x + eps >= y; }

template<class T> inline T sqr(T x) { return x * x; }

const int MAXV = 200010;
const int MAXE = 2000010;
const int orig = 0, dest = MAXV - 1;

struct Edge {
    int v;
    double c, f; // capa, flow
    Edge *next;
    Edge *rev; // revese edge
};
Edge e_buf[MAXE];
Edge *e_head[MAXV];
Edge *e_work[MAXV];
Edge *e_tail;

int que[MAXV], lev[MAXV];

inline void add_edge(int u, int v, double c)
{
    *e_tail = (Edge){v, c, 0, e_head[u]};
    e_head[u] = e_tail++;

    *e_tail = (Edge){u, 0, 0, e_head[v]};
    e_head[v] = e_tail++;

    e_head[u]->rev = e_head[v];
    e_head[v]->rev = e_head[u];
}

bool bfs()
{
    memset(lev, 0xff, sizeof(lev));

    int *head = que, *tail = que;
    *tail++ = orig;
    lev[orig] = 0;

    while (head != tail) {
        int u = *head++;
        for (Edge *e = e_head[u]; e; e = e->next)
            if (lev[e->v] == -1 && ls(e->f, e->c)) {
                lev[e->v] = lev[u] + 1;
                *tail++ = e->v;
            }
    }

    return lev[dest] > -1;
}

double dfs(int u, double f)
{
    if (u == dest) return f;

    double res = 0;
    for (Edge *&e = e_work[u]; e; e = e->next)
        if (lev[e->v] == lev[u] + 1 && ls(e->f, e->c)) {
            double tmp = dfs(e->v, fmin(f - res, e->c - e->f));
            res += tmp;
            e->f += tmp;
            e->rev->f = -e->f;
            if (eq(res, f)) break;
        }

    return res;
}

double dinic()
{
    double res = 0;
    while (bfs()) {
        for (int i = 0; i < (e_tail - e_buf); i++) e_work[i] = e_head[i];
        double tmp = dfs(orig, DINF);
        if (!eq0(tmp)) res += tmp;
        else break;
    }

    return res;
}

struct Point {
    double x, y;

    Point(double _x, double _y) : x(_x), y(_y) { }
};

inline double dist_sqr(const Point &a, const Point &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }
inline double dist(const Point &a, const Point &b) { return sqrt(dist_sqr(a, b)); }

struct Ship {
    Point S, E;
    int s, r, e;
    double length;

    Ship(const Point &_S, const Point &_E, int _s, int _r, int _e)
        : S(_S), E(_E), s(_s), r(_r), e(_e)
    {
        length = dist(S, E);
    }
};

pdd getx(const Point &P, const Point &A, const Point &B, double r)
{
    double r2 = sqr(r);
    double b2 = dist_sqr(A, P);
    double b = sqrt(b2);
    double cosPAB = (b2 + dist_sqr(A, B) - dist_sqr(B, P)) / (2 * b * dist(A, B));
    double delta = sqr(2 * b * cosPAB) - 4 * (b2 - r2);
    double x1, x2;

    if (ls(delta, 0)) {
        return pdd(-1, -1);
    }
    if (eq0(delta)) {
        x1 = x2 = 2 * b * cosPAB / 2.0;
    } else {
        x1 = (2 * b * cosPAB + sqrt(delta)) / 2.0;
        x2 = (2 * b * cosPAB - sqrt(delta)) / 2.0;
        if (gr(x1, x2)) swap(x1, x2);
    }

    if (ls(x2, 0)) return pdd(-1, -1);
    if (gr(x1, dist(A, B))) return pdd(-1, -1);
    x1 = fmax(x1, 0);
    x2 = fmin(x2, dist(A, B));

    return pdd(x1, x2);
}

class EllysDeathStars {
    private:

    public:
        double getMax(vector <string> stars, vector <string> ships)
        {
            memset(e_head, 0, sizeof(e_head));
            e_tail = e_buf;

            vector<Point> death;
            for (int i = 0; i < stars.size(); i++) {
                int x, y;
                sscanf(stars[i].c_str(), "%d%d", &x, &y);
                death.push_back(Point(x, y));
            }

            vector<Ship> lol;
            vector<double> time_point;
            for (int i = 0; i < ships.size(); i++) {
                int sx, sy, ex, ey, s, r, e;
                sscanf(ships[i].c_str(), "%d%d%d%d%d%d%d", &sx, &sy, &ex, &ey, &s, &r, &e);
                Point S(sx, sy), E(ex, ey);
                lol.push_back(Ship(S, E, s, r, e));

                time_point.push_back(dist(S, E) / s);
                for (int j = 0; j < death.size(); j++) {
                    pdd x = getx(death[j], S, E, r);
                    if (greq(x.first, 0)) {
                        time_point.push_back(x.first / s);
                        if (!eq(x.first, x.second)) {
                            time_point.push_back(x.second / s);
                        }
                    }
                }
            }

            sort(time_point.begin(), time_point.end());
            int time_point_cnt = 1;
            for (int i = 1; i < time_point.size(); i++) {
                if (!eq(time_point[i], time_point[time_point_cnt - 1])) {
                    time_point[time_point_cnt++] = time_point[i];
                }
            }

            for (int i = 0; i < lol.size(); i++) {
                add_edge(orig, i + 1, lol[i].e);
            }

            for (int i = 1; i < time_point_cnt; i++) {
                double interval = time_point[i] - time_point[i - 1];
                double mid_time = time_point[i - 1] + interval / 2.0;
                for (int j = 0; j < death.size(); j++) {
                    add_edge(lol.size() + i * death.size() + j + 1, dest, interval);
                }
                for (int j = 0; j < lol.size(); j++) {
                    if (gr(time_point[i] * lol[j].s, lol[j].length)) continue;
                    double mid_dist = mid_time * lol[j].s;
                    double dx = mid_dist / lol[j].length * (lol[j].E.x - lol[j].S.x);
                    double dy = mid_dist / lol[j].length * (lol[j].E.y - lol[j].S.y);
                    Point mid(lol[j].S.x + dx, lol[j].S.y + dy);
                    for (int k = 0; k < death.size(); k++) {
                        if (ls(dist(mid, death[k]), lol[j].r)) {
                            add_edge(j + 1, lol.size() + i * death.size() + k + 1, interval);
                        }
                    }
                }
            }

            return dinic();
        }
};
