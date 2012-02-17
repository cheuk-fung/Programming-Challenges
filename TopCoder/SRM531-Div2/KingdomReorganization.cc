#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int u, v, d;

    Edge(int _u, int _v, int _d) : u(_u), v(_v), d(_d) { }
    bool operator <(const Edge &other) const { return d < other.d; }
};

class DisjointSet {
    private:
        int size;
        int *p;

    public:
        DisjointSet(int _size)
            : size(_size)
        {
            p = new int[size];
            reset();
        }

        void reset()
        {
            for (int i = 0; i < size; i++) p[i] = i;
        }

        int find(int u)
        {
            if (p[u] == u) return u;
            return p[u] = find(p[u]);
        }

        void join(int u, int v)
        {
            int x = find(u),
                y = find(v);
            if (x != y) p[x] = y;
        }
};

class KingdomReorganization {
    private:
        int getValue(char c)
        {
            return isupper(c) ? c - 'A' : c - 'a' + 26;
        }

        int kruskal(vector<Edge> &e, DisjointSet &ds)
        {
            int res = 0;

            sort(e.begin(), e.end());
            for (vector<Edge>::const_iterator it = e.begin(); it != e.end(); it++)
                if (ds.find(it->u) != ds.find(it->v)) {
                    ds.join(it->u, it->v);
                    res += it->d;
                }

            return res;
        }

    public:
        int getCost(vector <string> kingdom, vector <string> build, vector <string> destroy)
        {
            int n = kingdom.size();
            DisjointSet ds(n);
            vector<Edge> e;


            int res = 0;

            for (int i = 0; i < n; i++)
                for (int j = 0; j < i; j++)
                    if (kingdom[i][j] == '0')
                        e.push_back(Edge(i, j, getValue(build[i][j])));
                    else {
                        int d = getValue(destroy[i][j]);
                        e.push_back(Edge(i, j, -d));
                        res += d;
                    }

            return res += kruskal(e, ds);
        }
};
