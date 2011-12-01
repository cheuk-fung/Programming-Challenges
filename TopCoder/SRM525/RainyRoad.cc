#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

using std::vector;
using std::string;

class RainyRoad {
    private:
        bool vis[2][100];

        void floodfill(int x, int y, const vector<string> &road)
        {
            if (vis[x][y]) return ;
            if (road[x][y] == 'W') return ;

            vis[x][y] = 1;

            floodfill(x ^ 1, y, road);
            if (y + 1 < road[0].length()) {
                floodfill(0, y + 1, road);
                floodfill(1, y + 1, road);
            }
        }

    public:
        string isReachable(vector<string> road)
        {
            memset(vis, 0, sizeof(vis));
            floodfill(0, 0, road);
            return vis[0][road[0].length() - 1] ? "YES" : "NO";
        }
};

int main()
{
    vector<string> road;
    road.push_back(".W..W..");
    road.push_back("...WWW.");

    RainyRoad RR;
    printf("%s\n", RR.isReachable(road).c_str());

    return 0;
}
