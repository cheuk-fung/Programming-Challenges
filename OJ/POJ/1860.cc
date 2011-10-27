/*
 *  SRC: POJ 1860
 * PROB: Currency Exchange
 * ALGO: Bellman Ford
 * DATE: Jul 12, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <vector>

using std::vector;

const double eps = 1e-12;
const int MAXN = 110;

struct Edge
{
    int u, v;
    double r, c;

    Edge(int uu, int vv, double rr, double cc)
        : u(uu), v(vv), r(rr), c(cc)
    { }
};

vector<Edge> edge;

double greatest[MAXN + 1];

int n, m, s;
double money;

bool bellmanFord()
{
    greatest[s] = money;

    for (int i = 0; i < n - 1; i++) {
        for (vector<Edge>::const_iterator e = edge.begin(); e != edge.end(); e++) {
            double exchange = (greatest[e->u] - e->c) * e->r;
            if (exchange - eps > greatest[e->v])
                greatest[e->v] = exchange; 
        }

        if (greatest[s] - eps > money) return true;
    }

    for (vector<Edge>::const_iterator e = edge.begin(); e != edge.end(); e++) {
        double exchange = (greatest[e->u] - e->c) * e->r;
        if (exchange - eps > greatest[e->v])
            return true;
    }

    return false;
}

int main()
{
    scanf("%d%d%d%lf", &n, &m, &s, &money);

    for (int i = 0; i < m; i++) {
        int u, v;
        double r, c;
        scanf("%d%d", &u, &v);

        scanf("%lf%lf", &r, &c);
        edge.push_back(Edge(u, v, r, c));

        scanf("%lf%lf", &r, &c);
        edge.push_back(Edge(v, u, r, c));
    }

    if (bellmanFord()) puts("YES");
    else puts("NO");

    return 0;
}
