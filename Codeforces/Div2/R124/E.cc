#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int>::const_iterator vci;

vector<int> edge[2000];
int ans[2000];
int size[2000];

struct Point {
    long long x, y;
    int idx;

    Point(long long _x, long long _y, int _idx) : x(_x), y(_y), idx(_idx) { }

    bool operator<(const Point &o)
    {
        return y < o.y;
    }
};
vector<Point> pnt;

class Compare_Angle {
    private:
        Point base;

    public:
        Compare_Angle(const Point &_base) : base(_base) { }
        bool operator()(const Point &a, const Point &b) const
        {
            return (a.x - base.x) * (b.y - base.y) - (b.x - base.x) * (a.y - base.y) > 0;
        }
};

int make_tree(int x, int parent)
{
    size[x] = 1;
    for (vci it = edge[x].begin(); it != edge[x].end(); it++) {
        if (*it != parent) {
            size[x] += make_tree(*it, x);
        }
    }
    return size[x];
}

void make_match(int x, int parent, vector<Point>::iterator start, vector<Point>::iterator end)
{
    vector<Point>::iterator low = min_element(start, end);
    ans[low->idx] = x;
    swap(*start, *low);
    sort(start + 1, end, Compare_Angle(*start));

    start++;
    for (vci it = edge[x].begin(); it != edge[x].end(); it++) {
        if (*it != parent) {
            make_match(*it, x, start, start + size[*it]);
            start += size[*it];
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        pnt.push_back(Point(x, y, i));
    }

    make_tree(1, 0);
    make_match(1, 0, pnt.begin(), pnt.end());

    for (int i = 0; i < n; i++) cout << ans[i] << endl;

    return 0;
}

